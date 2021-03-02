/* bankAccount.h simulates a simple bank account
 *
 * Joel Adams, Calvin College, Fall 2013.
 */


// Shared Variables
pthread_mutex_t balance_lock;
double bankAccountBalance = 0;

// add amount to bankAccountBalance
void deposit(double amount) {
   pthread_mutex_lock(&balance_lock);
   bankAccountBalance += amount;
   pthread_mutex_unlock(&balance_lock);
   
}

// subtract amount from bankAccountBalance
void withdraw(double amount) {
   pthread_mutex_lock(&balance_lock);
   bankAccountBalance -= amount;
   pthread_mutex_unlock(&balance_lock);
}

void cleanup() {
   pthread_mutex_destroy(&balance_lock);
}

