//
// Created by Роман Агеев on 2019-07-04.
//

#ifndef VECTOR_MOVE_VECTOR_HPP
#define VECTOR_MOVE_VECTOR_HPP

#include <variant>
#include <memory>
#include <cassert>

template<typename T, typename Tr>
struct vector_iterator {
 private:
  template<typename, typename> friend struct vector;
  template<typename, typename> friend struct const_vector_iterator;
  explicit vector_iterator(T* in) : pointer_(in) {}

  T* pointer_ = nullptr;

 public:
  typedef std::random_access_iterator_tag     iterator_category;
  typedef T                                   value_type;
  typedef T &                                  reference;
  typedef typename Tr::difference_type    difference_type;
  typedef typename Tr::pointer            pointer;

  vector_iterator() = default;
  vector_iterator(vector_iterator const&) = default;
  vector_iterator& operator=(vector_iterator const&) = default;

  reference operator[](size_t i) {
    return pointer_[i];
  }

  reference operator*() const {
    return *pointer_;
  }

  pointer operator->() const {
    return pointer_;
  }

  vector_iterator& operator++() {
    ++pointer_;
    return *this;
  }

  const vector_iterator operator++(int) {
    vector_iterator tmp(*this);
    ++*this;
    return tmp;
  }

  vector_iterator& operator--() {
    --pointer_;
    return *this;
  }

  const vector_iterator operator--(int) {
    vector_iterator tmp(*this);
    --*this;
    return tmp;
  }

  vector_iterator& operator+=(size_t i) {
    pointer_ += i;
    return *this;
  }

  vector_iterator& operator-=(size_t i) {
    pointer_ -= i;
    return *this;
  }

  friend difference_type operator-(vector_iterator const& in1, vector_iterator const& in2) {
    return in1.pointer_ - in2.pointer_;
  }

  friend vector_iterator operator+(vector_iterator in, size_t i) {
    in += i;
    return in;
  }

  friend vector_iterator operator-(vector_iterator in, size_t i) {
    in -= i;
    return in;
  }

  friend vector_iterator operator+(size_t i, vector_iterator in) {
    in += i;
    return in;
  }

  friend bool operator<(vector_iterator const& in1, vector_iterator const& in2) {
    return in1.pointer_ < in2.pointer_;
  }
  friend bool operator>(vector_iterator const& in1, vector_iterator const& in2) {
    return in2 < in1;
  }
  friend bool operator<=(vector_iterator const& in1, vector_iterator const& in2) {
    return (in1 < in2) || (in1 == in2);
  }
  friend bool operator>=(vector_iterator const& in1, vector_iterator const& in2) {
    return (in1 > in2) || (in1 == in2);
  }
  friend bool operator==(vector_iterator const& in1, vector_iterator const& in2) {
    return in1.pointer_ == in2.pointer_;
  }
  friend bool operator!=(vector_iterator const& in1, vector_iterator const& in2) {
    return !(in1 == in2);
  }
};

template<typename T, typename Tr>
struct const_vector_iterator {
 private:
  template<typename,typename> friend class vector;

  explicit const_vector_iterator(T const * p) : pointer_(p) {}

  T const * pointer_ = nullptr;
 public:
  typedef std::random_access_iterator_tag     iterator_category;
  typedef T                                   value_type;
  typedef T const &                                  reference;
  typedef typename Tr::difference_type    difference_type;
  typedef typename Tr::const_pointer            pointer;
  const_vector_iterator() = default;
  const_vector_iterator(const_vector_iterator const&) = default;
  const_vector_iterator(vector_iterator<T, Tr> const&in) : pointer_(in.pointer_) {}
  const_vector_iterator& operator=(const_vector_iterator const&) = default;

  reference operator[](size_t i) {
    return pointer_[i];
  }

  reference operator*() const {
    return *pointer_;
  }

  pointer operator->() const {
    return pointer_;
  }

  const_vector_iterator& operator++() {
    ++pointer_;
    return *this;
  }

  const const_vector_iterator operator++(int) {
    vector_iterator tmp(*this);
    ++*this;
    return tmp;
  }

  const_vector_iterator& operator--() {
    --pointer_;
    return *this;
  }

  const const_vector_iterator operator--(int) {
    const_vector_iterator tmp(*this);
    --*this;
    return tmp;
  }

  const_vector_iterator& operator+=(size_t i) {
    pointer_ += i;
    return *this;
  }

  const_vector_iterator& operator-=(size_t i) {
    pointer_ -= i;
    return *this;
  }

  friend difference_type operator-(const_vector_iterator const& in1, const_vector_iterator const& in2) {
    return in1.pointer_ - in2.pointer_;
  }

  friend const_vector_iterator operator+(const_vector_iterator in, size_t i) {
    in += i;
    return in;
  }

  friend const_vector_iterator operator-(const_vector_iterator in, size_t i) {
    in -= i;
    return in;
  }

  friend const_vector_iterator operator+(size_t i, const_vector_iterator in) {
    in += i;
    return in;
  }

  friend bool operator<(const_vector_iterator const& in1, const_vector_iterator const& in2) {
    return in1.pointer_ < in2.pointer_;
  }
  friend bool operator>(const_vector_iterator const& in1, const_vector_iterator const& in2) {
    return in2 < in1;
  }
  friend bool operator<=(const_vector_iterator const& in1, const_vector_iterator const& in2) {
    return (in1 < in2) || (in1 == in2);
  }
  friend bool operator>=(const_vector_iterator const& in1, const_vector_iterator const& in2) {
    return (in1 > in2) || (in1 == in2);
  }
  friend bool operator==(const_vector_iterator const& in1, const_vector_iterator const& in2) {
    return in1.pointer_ == in2.pointer_;
  }
  friend bool operator!=(const_vector_iterator const& in1, const_vector_iterator const& in2) {
    return !(in1 == in2);
  }
};


template<typename T, typename Alloc = std::allocator<T>>
class vector {
 public:
  typedef T value_type;
  typedef T& reference;
  typedef T const & const_reference;
  typedef Alloc allocator_type;
  typedef std::allocator_traits<Alloc>  allocator_traits;
  typedef typename allocator_traits::difference_type  difference_type;
  typedef typename allocator_traits::size_type        size_type;
  typedef typename allocator_traits::pointer          pointer;
  typedef typename allocator_traits::const_pointer    const_pointer;
  typedef vector_iterator<T, allocator_traits>       iterator;
  typedef const_vector_iterator<T, allocator_traits> const_iterator;
  typedef std::reverse_iterator<iterator>         reverse_iterator;
  typedef std::reverse_iterator<const_iterator>   const_reverse_iterator;
 private:
  typedef typename allocator_traits::template rebind_alloc<uint8_t> data_allocator;
  typedef typename std::allocator_traits<data_allocator> data_allocator_traits;

  struct helper {
    size_type size = 0;
    size_type capacity = 0;
    pointer ptr = nullptr;
  };

  typedef helper * helper_ptr;
  data_allocator alloc;
  helper_ptr data_ = nullptr;

  [[nodiscard]] helper_ptr allocate_(size_type cap) {
    auto tmp = reinterpret_cast<helper_ptr>
        (data_allocator_traits::allocate(alloc_(), sizeof(helper) + cap * sizeof(T)));
    tmp->size = 0;
    tmp->capacity = cap;
    tmp->ptr = reinterpret_cast<pointer>(&(tmp->ptr) + 1);;
    return tmp;
  }

  void deallocate_helper(helper_ptr & in) noexcept {
    if (in != nullptr) {
      data_allocator_traits::deallocate(alloc_(),
          reinterpret_cast<uint8_t *>(in), sizeof(helper) + in->capacity * sizeof(T));
      in = nullptr;
    }
  }

  void deallocate_() noexcept {
    if (data_ != nullptr) {
      std::destroy(ptr_(), ptr_() + size());
      deallocate_helper(data_);
    }
  }

  size_type capacity_() const noexcept {
    return data_->capacity;
  }

  pointer ptr_() const noexcept {
    return data_->ptr;
  }

  data_allocator & alloc_() noexcept {
    return alloc;
  }

  data_allocator const & alloc_() const noexcept {
    return alloc;
  }

  template<typename...Args>
  void push_back_short(Args&&...in) {
      data_allocator_traits::construct(alloc_(), ptr_() + size(), std::forward<Args>(in)...);
  }

  template<typename...Args>
  void push_back_long(Args&&...in) {
    auto new_ptr = allocate_(capacity_() * 2);
    new_ptr->size = size();
    try {
      data_allocator_traits::construct(alloc_(), new_ptr->ptr + size(), std::forward<Args>(in)...);
    } catch(...) {
      deallocate_helper(new_ptr);
      throw;
    }
    try {
      if constexpr (!std::is_nothrow_move_constructible_v<value_type>
          && std::is_copy_constructible_v<value_type>) {
        std::uninitialized_copy(ptr_(), ptr_() + size(), new_ptr->ptr);
      } else {
        std::uninitialized_move(ptr_(), ptr_() + size(), new_ptr->ptr);
      }
    } catch(...) {
      std::destroy_at(new_ptr->ptr + size());
      deallocate_helper(new_ptr);
      throw;
    }
    clear();
    data_ = new_ptr;
  }

 public:
  vector() noexcept = default;

  vector(vector const &in) {
    if (!in.empty()) {
      data_ = allocate_(in.capacity_());
      try {
        std::uninitialized_copy(in.ptr_(), in.ptr_() + in.size(), ptr_());
      } catch (...) {
        deallocate_();
        throw;
      }
      data_->size = in.size();
    }
  }

  vector(vector&& in) noexcept {
    swap(in);
  }

  vector &operator=(vector const & in) {
    if (this != &in) {
      vector tmp = in;
      clear();
      swap(tmp);
    }
    return *this;
  }

  vector &operator=(vector&& in) noexcept {
    clear();
    swap(in);
    return *this;
  }

  ~vector() noexcept {
    clear();
  }

  void clear() noexcept {
    deallocate_();
  }

  size_type size() const noexcept {
    return data_ == nullptr ? 0 : data_->size;
  }

  bool empty() const noexcept {
    return data_ == nullptr;
  }

  void push_back(const_reference in) { // strong
    if (empty()) {
      data_ = allocate_(8);
      try {
        push_back_short(in);
      } catch(...) {
        deallocate_();
        throw;
      }
    } else if (size() < capacity_()) {
      push_back_short(in);
    } else {
      push_back_long(in);
    }
    ++data_->size;
  }

  void push_back(T&& in) { // strong
    if (empty()) {
      data_ = allocate_(8);
      try {
        push_back_short(std::move(in));
      } catch(...) {
        deallocate_();
        throw;
      }
    } else if (size() < capacity_()) {
      push_back_short(std::move(in));
    } else {
      push_back_long(std::move(in));
    }
    ++data_->size;
  }

  void pop_back() noexcept {
    std::destroy_at(ptr_() + size() - 1);
    --data_->size;
    if (data_->size == 0) {
      clear();
    }
  }

  template <typename... Args>
  void emplace_back(Args&&... args) { //strong
    if (empty()) {
      data_ = allocate_(8);
      try {
        push_back_short(std::forward(args...));
      } catch(...) {
        deallocate_();
        throw;
      }
    } else if (size() < capacity_()) {
      push_back_short(std::forward(args...));
    } else {
      push_back_long(std::forward(args...));
    }
    ++data_->size;
  }

  reference operator[](size_type i) noexcept {
    return ptr_()[i];
  }

  const_reference operator[](size_type i) const noexcept {
    return ptr_()[i];
  }

  pointer data() noexcept {
    return size() == 0 ? nullptr : ptr_();
  }

  const_pointer data() const noexcept {
    return size() == 0 ? nullptr :ptr_();
  }

  void swap(vector & in) noexcept {
    std::swap(data_, in.data_);
  }

  const_reference front() const noexcept {
    return ptr_()[0];
  }

  reference front() noexcept {
    return ptr_()[0];
  }

  const_reference back() const noexcept {
    return ptr_()[size() - 1];
  }

  reference back() noexcept {
    return ptr_()[size() - 1];
  }

  iterator begin() noexcept {
    return iterator(data());
  }

  iterator end() noexcept {
    return iterator(data() + size());
  }

  const_iterator begin() const noexcept {
    return const_iterator(data());
  }

  const_iterator end() const noexcept {
    return const_iterator(data() + size());
  }

  const_iterator cbegin() const noexcept {
    return begin();
  }

  const_iterator cend() const noexcept {
    return end();
  }

  const_reverse_iterator rbegin() const noexcept {
    return const_reverse_iterator(cend());
  }

  const_reverse_iterator rend() const noexcept {
    return const_reverse_iterator(cbegin());
  }

  reverse_iterator rbegin() noexcept {
    return reverse_iterator(end());
  }

  reverse_iterator rend() noexcept {
    return reverse_iterator(begin());
  }

  const_reverse_iterator rcbegin() const noexcept {
    return const_reverse_iterator(cend());
  }

  const_reverse_iterator rcend() const noexcept {
    return const_reverse_iterator(cbegin());
  }
};
#endif //VECTOR_MOVE_VECTOR_HPP
