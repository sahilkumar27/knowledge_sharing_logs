class MyStack {
public:
    queue<int> q1;
    queue<int> q2;
    MyStack() {
        
    }
    
    void push(int x) {
        q1.push(x);
    }
    
    int pop() {
        while(q1.size()>1){
            q2.push(q1.front());
            q1.pop();
        }

        int poppedValue=q1.front();
        q1.pop();
        swap(q1,q2);
        return poppedValue;
    }
    
    int top() {
        while(q1.size()>1){
            q2.push(q1.front());
            q1.pop();
        }

        int topValue=q1.front();
        q1.pop();
        q2.push(topValue);
        swap(q1,q2);
        return topValue;
    }
    
    bool empty() {
        return q1.empty();
    }
};