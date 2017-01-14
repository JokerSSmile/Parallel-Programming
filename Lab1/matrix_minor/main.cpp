#include "stdafx.h"
#include "ThreadedMatrixRank.h"
#include "LinearMatrixRank.h"

using namespace std;

int main(int argc, char* argv[])
{
    if (argc == 2)
    {
        CThreadedMatrixRank threadedAgreagator(MATRIX);
        //threadedAgreagator.SetThreadsCount(atoi(argv[1]));
		threadedAgreagator.SetThreadsCount(4);
        cout << threadedAgreagator.GetRang() << endl;
    }
    float first = float(clock());
    cout << first / CLOCKS_PER_SEC << endl;

    CLinearMatrixRank lineAgregator(MATRIX);
    cout << lineAgregator.GetRang() << endl;
    cout << (float(clock()) - first) / CLOCKS_PER_SEC;
    return 0;
}

