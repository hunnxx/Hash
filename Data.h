#ifndef DATA_H
#define DATA_H

class Data{
    int input_cnt;
    int replace_cnt;
    int resize_cnt;
    int prob_cnt;
public:
    Data();
    int getInputCnt();
    int getReplaceCnt();
    int getResizeCnt();
    int getProbCnt();
    void increaseInputCnt();
    void increaseReplaceCnt();
    void increaseResizeCnt();
    void increaseProbCnt();
    void reset();
    void print(int size, int capacity);
};

#endif // ifndef DATA_H