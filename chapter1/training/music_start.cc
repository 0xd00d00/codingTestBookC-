// 이중 연결 리스트를 사용하기가 애매한 응용프로그램을 만들자
//
// 여러 명의 사용자가 순서대로 진행하는 구조를 변경해서 사용해야하는 경우가 발생함.
//
// 원형 연결리스트를 구현해야함
//
//
// singly_node로 할거면 tail필요. 안하면 너무 순회를 많이 해야됨.

#include <cstddef>
#include <iostream>
#include <string>

// 1. 여러개의 음악을 이용하여 재생목록을 생성할 수 있어야함.
// 2. 재생 목록에 음악을 추가할 수 있어야함.
// 3. 재생 목록에 음악을 제거할 수 있어야힘.
// 4. 음악을 순환적으로 재생할 수 있어야함. (구현은 노래제목 출력으로 대신)

// 1. 먼저 원형 데이터 표현을 지원하는 기본구조 설계

struct singly_node {
  std::string music_name_;
  singly_node* next_;
};

class circular_linked_list {
public:
  using node=singly_node;
  using node_ptr=singly_node*;

private:
  // 초기화 하지 않은 bus error남.
  node_ptr head = nullptr;
  node_ptr tail = nullptr;
public:
  // 2. node를 삽입하고 삭제할 수 있어야함.
  // 지금은 일자로 삽입한거임 -> 원형으로 삽입하도록 만들어야지
  // 난 싱그리로 구현한다.
  //
  // 그림 그려가면서 코딩해야함.
  // 그게 가장 빠름.
  // void push_back(std::string music_name) {
  //   node_ptr tmp = new node{ music_name, nullptr };
  //
  //   if (head == nullptr) {
  //     head = tmp;
  //     tail = tmp;
  //     tmp->next_ = head;
  //     return;
  //   }
  //
  //   // 최신을 가장 마지막에 유지
  //   tmp->next_ = head->next_;
  //   head->next_ = tmp;
  // }


  // dummy를 놔두고 넣어야함. 만약 할 거면

  circular_linked_list() {
    head = tail = new node { "", nullptr };
    head->next_ = head;
  }

  void push_back(std::string music_name) {
    node_ptr tmp = new node { music_name, nullptr };
    tmp->next_ = head;
    tail->next_ = tmp;
    tail = tmp;

  }

  void pop_back() {
    if (head->next_ == tail) {
      // 끝난거임..
      std::cout << "여기 ? ";
      delete tail;
      tail = nullptr;
      delete head;
      head = nullptr;
      return;
    }

    auto tmp = head->next_;
    while ( true ) {
      if (tmp->next_ == tail) {
        tmp->next_ = head;
        delete tail;
        tail = tmp;
        break;
      }
    }
  }


  // void pop_back() {
  //
  //   if (head == tail) {
  //     head = tail = nullptr;
  //     return;
  //   }
  //
  //   auto tmp = tail;
  //   tail = tmp->next_;
  //   head_next_ = tail;


    /*
    auto tmp = head;
    while(true) {
      if (head == tmp->next_) {
        tmp->next_ = next; 
        break;
      }
      tmp = tmp->next_;
    }
    head = next;
    */

    // tail 없으면 위 처럼 돌아야함.
    //
   // }


  // error: use of non-static data member 'head' of 'circular_linked_list' from nested type 'circular_ll_iter' 
  // 위와 같은 에러가 나옴. -> begin, end를 만들 경우
  // iterator
  struct circular_ll_iter {
    private:
      node_ptr ptr_;

    public:
      circular_ll_iter(node_ptr ptr) : ptr_(ptr) {};

      std::string& operator*() { return ptr_->music_name_; }
      node_ptr get() { return ptr_; }

      // for each를 사용할 수 있게 하려면 => ++, ++(int) == != begin end를 구현해야됨.

      circular_ll_iter& operator++() {
        ptr_ = ptr_->next_;
        return *this;
      }

      circular_ll_iter operator++(int) {
        circular_ll_iter result = *this;
        ++(*this);
        return result;
      }

      friend bool operator==(const circular_ll_iter& left,
          const circular_ll_iter& right) {
        return left.ptr_ == right.ptr_;
      }
      friend bool operator!=(const circular_ll_iter& left,
          const circular_ll_iter& right) {
        return left.ptr_ != right.ptr_;
      }
  };

  // iterator 안에 있는거 아니다.
  circular_ll_iter begin() { return circular_ll_iter(head->next_); }
  // end는 그전껄 가리켜야함.
  circular_ll_iter end() { return circular_ll_iter(head); }
  circular_ll_iter begin() const { return circular_ll_iter(head); }
  circular_ll_iter end() const { return circular_ll_iter(tail); }

  // 반복자 활용
  void printall() {
    auto tmp = head;
    while (true && tmp != nullptr) {
      std::cout << "뮤직 네임 " << tmp->music_name_ << std::endl;
      tmp = tmp->next_;

      if (head == tmp) {
        std::cout << "끝.."<< std::endl;
        break;
      }
    }
  }
};

int main() {


  circular_linked_list test;
  test.push_back("kim");
  test.push_back("lee");

  test.pop_back();
  test.pop_back();
 // for (auto i : test)
 //   std::cout << i << std::endl;
  /*
  test.printall();

  test.pop_back();
  test.printall();

  test.pop_back();
  test.printall();
  */
}
