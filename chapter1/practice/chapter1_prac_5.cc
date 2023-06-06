#include <iostream>
#include <algorithm>

using namespace std;

struct singly_ll_node
{
  int data_;
  singly_ll_node* next_;
};

// 1. singly_ll 클래스 구현, 위 노드를 연결해서 사용하는 linked list이다.

class singly_ll {
public:
  using node = singly_ll_node;
  using node_ptr = node*; // 위에 먼저 정의 해뒀으니, singly_ll_node를 또 쓸 필요는 없지.

private:
  node_ptr head;

// 2. std::forward_list 클래스에 있는 push_front, pop_front 함수 구현
//  여기서 포인트는 -> push_front : 앞에꺼 꺼냄.
//  pop_front 꺼내주고 삭제.

public:
  void push_front(int val) {
    // node 만들어야지.
    // nullptr인게 아직 연결되지 않은 순수한 node임.
    auto new_node = new node { val, nullptr };

    if (head != nullptr)
      new_node->next_ = head;
    head = new_node;

    // 만약 head == nullptr로 구별했다면 소스코드가 더 복자해졌을 것..
    // if (head == nullptr) {
    //  head = new_node;
    //  return;
    // }
    //
    // new_node->next = head;
    // head = new_node;
    //
    // 위 코드를 더 간단하게 만드는거지.
  }

  void pop_front() {
    // 가장 앞에걸 꺼내주면 됨.
    auto first = head;
    if (head) {
      head = head->next_;
      delete first;
    }

    // head가 없다면 꺼낼 필요가 없음.
    // pop_front는 데이터를 내주는게 아니라 그냥 지우는거다.
  }

  // 3. singly_ll 반복자 구현
  //  * 포인트1. 생성자
  //  * 포인트2. 접근자 가짐.
  //

  struct singly_ll_iterator {
    // node pointer를 가짐.
    private:
      node_ptr ptr;

    public:
      singly_ll_iterator(node_ptr p) : ptr(p) {}

      int& operator*() { return ptr->data_; }
      node_ptr get() { return ptr; }

      // 4. 선행 및 후행 증가 ++ 연산자 구현
      singly_ll_iterator& operator++() // 선행증가
      {
        ptr = ptr->next_;
        return *this;
      }

      // 위 함수를 이용하는거야!
      singly_ll_iterator operator++(int) // 후행증가
      {
        singly_ll_iterator result_iter = *this;
        ++(*this);
        return result_iter;
      }

      // 5. 두 반복자 같은지 판단하는 관계 연산자 함수를 friend로 정의
      friend bool operator==(const singly_ll_iterator& left,
                             const singly_ll_iterator& right)
      {
        return left.ptr == right.ptr;
      }
      friend bool operator!=(const singly_ll_iterator& left,
                             const singly_ll_iterator& right)
      {
        return left.ptr != right.ptr;
      }
  };

  singly_ll_iterator begin() { return singly_ll_iterator(head); }
  singly_ll_iterator end() { return singly_ll_iterator(nullptr); }
  singly_ll_iterator begin() const { return singly_ll_iterator(head); }
  singly_ll_iterator end() const { return singly_ll_iterator(nullptr); }

  // 6. 기본생성자, 깊은복사를 위한 복사생성자, 초기화리스트를 사용하는 생성자 구현
  singly_ll() = default;
  singly_ll(const singly_ll& other) : head(nullptr) {
    if (other.head) {
      head = new node { 0, nullptr };
      auto cur = head;
      auto it = other.begin();
      while (true) {
        cur->data_ = *it;

        auto temp = it;
        ++temp;
        if (temp == other.end())
          break;

        cur->next_ = new node {0, nullptr};
        cur = cur->next_;
        it = temp;
      }
    }
  }

  singly_ll(const std::initializer_list<int>& ilist) : head(nullptr) {
    for (auto it = std::rbegin(ilist); it != std::rend(ilist); it++) 
      push_front(*it);

    // 뒤로 추가하는것이 아닌, 앞으로 추가하니, 값을 뒤에서부터 앞으로 넣어줌.
  }
};

int main() {
  singly_ll sll = { 1, 2, 3 };
  sll.push_front(0);

  std::cout << "첫 번째 리스트: ";
  for(auto i : sll)
    std::cout << i << " ";
  std::cout << std::endl;

  // initialzer..
  auto sll2 = sll;

  sll2.push_front(-1);

  std::cout << "첫 번째 리스트를 복사한 후, 맨 앞에 -1을 추가: ";

  for (auto i : sll2)
    std::cout << i << " ";
  std::cout << std::endl;

  std::cout << "깊은 복사 후 첫 번째 리스트: ";

  for(auto a : sll)
    std::cout << a << " ";
  std::cout << endl;
}
