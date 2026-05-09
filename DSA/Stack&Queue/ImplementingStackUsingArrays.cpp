class myStack {
  public:
    int start;
    int end;
    vector<int> arr;
    int size;
    myStack(int n) {
        // Define Data Structures
        start=-1;
        end=-1;
        size=n;
    }

    bool isEmpty() {
        // check if the stack is empty
        return start==-1;
    }

    bool isFull() {
        // check if the stack is full
        return end==size-1;
    }

    void push(int x) {
        // inserts x at the top of the stack
        if(end>=size-1) return;
        arr.push_back(x);
        if(start==-1) start++;
        end++;
    }

    void pop() {
        // removes an element from the top of the stack
        if(start==-1) return;
        arr.pop_back();
        if(end==0){
          start=-1;
          end=-1;
        } 
        else{
         end--;   
        }
    }

    int peek() {
        // Returns the top element of the stack
        if(start==-1) return -1;
        return arr[end];
    }
};