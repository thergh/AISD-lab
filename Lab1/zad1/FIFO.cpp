#include <iostream>

class FIFO{
    private:
        int array[1000];
        int head = -1;
        int tail = -1;

    public:
        FIFO(){};

        ~FIFO(){};

        void Add(int value){
            if(head == -1){
                head = 0;
            }
            if(tail >= 1000){
                std::cout << "Error: out of array space." << std::endl;
                return;
            }
            tail++;
            array[tail] = value;
            std::cout << "Added:\t" << value << std::endl;
        }

        int Pop(){
            if(tail < head || tail < 0){
                std::cout << "Error: no elements left to remove." << std::endl;
                return -1;
            }

            int value = array[head];
            head++;
            std::cout << "Removed:\t" << value << std::endl;
            return value;
        }

        void ListElements(){
            std::cout << "[";
            for(int i=head; i<=tail; i++){
                std::cout << array[i];
                if(i < tail){
                    std::cout  << ", ";
                }
            }
            std:: cout << "]" << std::endl;
            
        }
};

int main(){
    std::cout << "Adding values to the queue:" << std::endl;
    FIFO queue;

    for(int i=0; i<50; i++){
        queue.Add(i);
    }

    std::cout << "Removing values from the queue:" << std::endl;

    for(int i=0; i<50; i++){
        queue.Pop();
    }

    std::cout << "Listing values left in the queue:" << std::endl;
    queue.ListElements();

}