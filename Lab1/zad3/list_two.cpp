#include <iostream>
#include <random>
#include <time.h>

class List{
    private:
        class Node{
        public:
            int value;
            Node* next_node;
            Node* prev_node;

            Node(){};

            Node(int value){
                this->value = value;
                this->next_node = nullptr;
                this->prev_node = nullptr;
            };
        };

    public:
        Node* head;
        Node* tail;
        int length = 0;

        List(){
            this->head = nullptr;
            this->tail = nullptr;
        }

        ~List(){};

        // adds at the beginning of the list
        void insert(int value){

            if(head == nullptr){
                Node* new_node = new Node(value);
                new_node->next_node = new_node;
                new_node->prev_node = new_node;
                head = new_node;
                tail = new_node;
            }
            else{
                Node* new_node = new Node(value);
                new_node->next_node = head;
                new_node->prev_node = tail;
                head->prev_node = new_node;
                tail->next_node = new_node;
                head = new_node;
            }

            this->length++;
            return;
        }

        // removes from the beginning of the list
        int pop(){
            if(head == nullptr){
                std::cout << "Error: List is empty." << std::endl;
                return -1;
            }
            if(head == tail){
                int value = head->value;
                head = nullptr;
                tail = nullptr;
                this->length--;
                return value;
            }
            else{
                int value = head->value;
                head = head->next_node;
                head->prev_node = tail;
                tail->next_node = head;
                this->length--;
                return value;
            }
        }

        int peek(){
            if(head == nullptr){
                std::cout << "Error: List is empty." << std::endl;
                return -1;
            }
            return head->value;
        }

        void ListElements(){
            if(this->head == nullptr){
                std::cout << "[]" << std::endl;
                return;
            }
            Node* node = this->head;
            std::cout << "[";
            while(node != tail){
                std::cout << node->value << ", ";
                node = node->next_node;
            }
            std::cout << node->value << ", ";
            node = node->next_node;
            std::cout << "]" << std::endl;
        }

    int FindValue(int value){
        int position = 0;
        int i = 0;
        Node* node = this->head;
        while(i < this->length){
            if(node->value == value){
                return i;
            }
            node = node->next_node;
            i++;
        }
        // std::cout << "Value " << value << " not found." << std::endl;
        return -1;
    }

    int FindValueBackwards(int value){
        int position = 0;
        int i = 0;
        Node* node = this->head;
        while(i < this->length){
            if(node->value == value){
                return i;
            }
            node = node->prev_node;
            i++;
        }
        // std::cout << "Value " << value << " not found." << std::endl;
        return -1;
    }

};

List merge(List list1, List list2){
    if(list1.head == nullptr){
        return list2;
    }
    if(list2.head == nullptr){
        return list1;
    }
    
    List new_list;
    new_list = list2;
    new_list.tail->next_node = list1.head;
    new_list.tail = list1.tail;
    new_list.tail->next_node = new_list.head;
    new_list.length = list1.length + list2.length;
    return new_list;
}

int main(){

    // testing merge
    List list1;
    List list2;
    std::cout << "Creating the first list:" << std::endl;
    for(int i=0; i<10; i++){
        list1.insert(i);
        std::cout << "Inserted:\t" << i << std::endl;
    }
    std::cout << "Creating the second list:" << std::endl;
    for(int i=10; i<20; i++){
        list2.insert(i);
        std::cout << "Inserted:\t" << i << std::endl;
    }
    std::cout << "Merging the lists:" << std::endl;
    List list3 = merge(list1, list2);
    list3.ListElements();



    std::cout << "Testing the cost of finding an element" << std::endl;
    srand(time(NULL));
    int arr[10000];
    for(int i=0; i<10000; i++){
        arr[i] = rand() % 100000;
    }
    List list4;
    for(int i=0; i<10000; i++){
        list4.insert(arr[i]);
    }

    // finding values that exist in the list
    long sum_present = 0;
    int cost = 0;
    int avg_cost_present = 0;
    for(int i=0; i<1000; i++){
        int random_index = rand() % 10000;
        // coinflipping to chose direction
        if(static_cast <float> (rand()) / static_cast <float> (RAND_MAX) <= 0.5){
            cost = list4.FindValue(arr[random_index]);
        }
        else{
            cost = list4.FindValueBackwards(arr[random_index]);
        }
        
        if(cost == -1){
            sum_present += 10000;
        }
        else{
            sum_present += cost;
        }
    }
    avg_cost_present = sum_present / 1000;
    std::cout << "Average cost of finding and element that's present in the list: "\
     << avg_cost_present << std::endl;
    

    // finding random values
    // finding values that exist in the list
    long sum_random = 0;
    cost = 0;
    int avg_cost_random = 0;
    for(int i=0; i<1000; i++){
        if(static_cast <float> (rand()) / static_cast <float> (RAND_MAX) <= 0.5){
            cost = list4.FindValue(rand() % 100000);
        }
        else{
            cost = list4.FindValueBackwards(rand() % 100000);
        }
        
        if(cost == -1){
            sum_random += 10000;
        }
        else{
            sum_random += cost;
        }
    }
    avg_cost_random = sum_random / 1000;
    std::cout << "Average cost of finding a random element: "\
     << avg_cost_random << std::endl;    
}

