#include <iostream>

class LIFO{
    private:
        int array[1000];
        int head = -1;
    
    public:
        void Add(int value){
            if(head >= 1000){
                std::cout << "Error: out of array space." << std::endl;
                return;
            }
            head ++;
            array[head] = value;
            std::cout << "Added:\t" << value << std::endl;
        }

        int Pop(){
            if(head < 0){
                std::cout << "Error: no elements left to remove." << std::endl;
                return -1;
            }
            int value = array[head];
            head--;
            std::cout << "Removed:\t" << value << std::endl;
            return value;
        }

        void ListElements(){
            std::cout << "[";
            for(int i=0; i<=head; i++){
                std::cout << array[i];
                if(i < head){
                    std::cout  << ", ";
                }

            }
            std:: cout << "]" << std::endl;
        }
};

int main(){
    std::cout << "Adding values to the stack:" << std::endl;
    LIFO stack;

    for(int i=0; i<50; i++){
        stack.Add(i);
    }

    std::cout << "Removing values from the stack:" << std::endl;

    for(int i=0; i<50; i++){
        stack.Pop();
    }

    std::cout << "Listing values left in the stack:" << std::endl;
    stack.ListElements();

}