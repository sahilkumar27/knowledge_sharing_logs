class myQueue {

  public:
    int *arr;
    int size;
    int capacity;
    myQueue(int n) {
        // Define Data Structures
        arr=new int[n];
        size=0;
        capacity=n;
    }

    bool isEmpty() {
        // check if the queue is empty
        return size==0;
    }

    bool isFull() {
        // check if the queue is full
        return size==capacity;
    }

    void enqueue(int x) {
        // Adds an element x at the rear of the queue.
        if(isFull()) return;
        
        arr[size]=x;
        size++;
    }

    void dequeue() {
        // Removes the front element of the queue.
        if(isEmpty()) return;
        
        for(int i=1;i<size;i++){
            arr[i-1]=arr[i];
        }
        
        size--;
    }

    int getFront() {
        // Returns the front element of the queue.
        if(isEmpty()) return -1;
        
        return arr[0];
    }

    int getRear() {
        // Return the last element of queue
        if(isEmpty()) return -1;
        
        return arr[size-1];
    }
};