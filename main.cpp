#include <iostream>
#include "History.hpp"
#include "Transaction.hpp"


#ifndef MARMOSET_TESTING
unsigned int Transaction::assigned_trans_id = 0;
int main() {

Transaction *T7 { new Transaction{"VGRO", 7, 8, 2020, true, 65, 3257.150}};
Transaction *T8 { new Transaction{"VGRO", 12, 5, 3019, true, 65, 4557.150}};
Transaction *T9 { new Transaction{"VGRO", 1, 16, 2090, false, 80, 4451.200}};
Transaction *T10 { new Transaction{"VGRO", 20, 17, 3000, true, 25, 1752.750}};
Transaction *T11 { new Transaction{"VGRO", 29, 4, 2019, false, 90, 6780.600}};
Transaction *T12 { new Transaction{"VGRO", 21, 12, 2018, true, 100, 9011.000}};
Transaction *T1 { new Transaction{"VGRO", 10, 9, 2007, true, 150, 10300.140}};
Transaction *T2 { new Transaction{"VGRO", 28, 12, 2048, true, 85, 7423.050}};
Transaction *T3 { new Transaction{"VGRO", 01, 4, 2018, true, 43, 3367.760}};
Transaction *T4 { new Transaction{"VGRO", 11, 11, 2018, true, 78, 7028.580}};
Transaction *T5 { new Transaction{"VGRO", 10, 12, 2018, false, 55, 5958.150}};
Transaction *T6 { new Transaction{"VGRO", 1, 12, 2102, false, 80, 2817.600}};

  History trans_history{};

  trans_history.insert(T12);
  trans_history.insert(T1);
  trans_history.insert(T11);
  trans_history.insert(T2);
  trans_history.insert(T10);
  trans_history.insert(T3);
  trans_history.insert(T9);
  trans_history.insert(T4);
  trans_history.insert(T8);
  trans_history.insert(T5);
  trans_history.insert(T7);
  trans_history.insert(T6);

  //trans_history.read_history();

  std::cout << "[Starting history]:" << std::endl;
  trans_history.print();
  trans_history.sort_by_date();

  std::cout << "[Sorted          ]:" << std::endl;
  trans_history.print();

  trans_history.update_acb_cgl();
  trans_history.print();

  std::cout << "[CGL for 2018    ]: " << trans_history.compute_cgl(2018) << std::endl;
  std::cout << "[CGL for 2019    ]: " << trans_history.compute_cgl(2019) << std::endl;

  return 0;

}
#endif
