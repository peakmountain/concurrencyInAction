#include <iostream>
#include <memory>

template <typename T>
class ThreadSafeQueue
{
    private:
        struct Node
        {
            T data;
            std::unique_ptr<Node> next;
            Node(T _data) : 
                data(std::move(_data))
            {}
        };
        std::unique_ptr<Node> head;
        Node* tail;

    public: 
        ThreadSafeQueue() 
        {
            head = std::move(std::unique_ptr<Node>());
            tail = nullptr;
        }

        ThreadSafeQueue(const ThreadSafeQueue& other) = delete;

        ThreadSafeQueue& operator= (const ThreadSafeQueue& other) = delete;

        bool empty()
        {
            return (head == nullptr);
        }

        void push(T _data)
        {
            std::unique_ptr<Node> p(new Node(_data));
            Node* new_tail = p.get();

            // std::cout << "push " << _data << std::endl;
                    
            if (tail == nullptr)
            {
                head = std::move(p);
            }
            else
            {
                tail->next = std::move(p);
            }

            tail = new_tail;
            
            // std::cout << "push done" << std::endl;
            std::cout << "head = " << head->data << std::endl;
        }

        std::shared_ptr<T> pop()
        {
            // std::cout << "pop start" << std::endl;

            if (!head)
            {
                return std::make_shared<T>();
            }


            std::shared_ptr<T> res(std::make_shared<T>(std::move(head->data)));
            std::unique_ptr<Node> old_head = std::move(head);
            head = std::move(old_head->next);
            // std::cout << "pop " << *res << std::endl;
            return res;
        }
};
