#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


int main()
{

    int n_A, n_B;
    vector<int> array_A;
    cin >> n_A;
    for (int i = 0; i < n_A; i++) {
        int temp;
        cin >> temp;
        array_A.push_back(temp);
    }
    sort(array_A.begin(), array_A.end());

    cin >> n_B;

    int l_bound_ind, r_bound_ind;
    for (int i = 0; i < n_B; i++)  {
        int l_bound, r_bound;
        cin >> l_bound >> r_bound;

        int right = n_A - 1;
        int left = 0;
        if ((array_A[n_A - 1] < l_bound) || (array_A[0] > r_bound)) {
            int kol_el = 0;
            cout << kol_el << "\n";
            continue;
        }
        else {
           while (right > left + 1) {
                int pivot = (left + right) / 2;
                int el_pivot = array_A[pivot];
                if (l_bound <= el_pivot)
                    right = pivot;
                else
                    left = pivot;
           }
           if (array_A[left] >= l_bound)
                l_bound_ind = left;
           else
                l_bound_ind = right;

        }

        right = n_A - 1;
        left = 0;
        while (right > left + 1) {
            int pivot = (left + right) / 2;
            int el_pivot = array_A[pivot];
            if (r_bound < el_pivot)
                right = pivot;
            else
                left = pivot;
        }
        if (array_A[right] <= r_bound)
             r_bound_ind = right;
        else
             r_bound_ind = left;

        int kol_el = r_bound_ind - l_bound_ind + 1;
        cout << kol_el << "\n";
    }
}
