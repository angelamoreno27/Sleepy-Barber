# Sleepy-Barber
The Sleepy Barber Problem is a hypothetical barber shop with only one barber, one barber chair, a certain amount of waiting chairs, and many customers walking into the shop. If customers walk into the shop and there are waiting chairs available then they take a seat and wake up the barber so they can be moved to the barber chair and get a haircut from the barber. If a customer walks into the shop and there are no available seats then the customer leaves the barbershop with no haircut. If a customer walks into the barber shop and there are available waiting chairs but not the barber chair then they can take a seat in a waiting chair and wait for the barber to become available to cut their hair.

My solution includes 3 semaphores which are 1. semaphore mutex 2. semaphore chair and 3. semaphore waitingCustomer. Semaphore mutex is used to ensure mutual exclusion to protect the critical section of the code so that shared resources are not modified incorrectly. The semaphore chair is used when the customer goes on to take a the barber seat now that the barber has availibility for a haircut. The semaphore waitingCustomer is used to let the barber know that there is a customer in his waiting chairs waiting for a haircut.

In the main() function, first we initialize our three semaphores, declare customer and barber threads, loops through the new threads, and finally destroys all semaphores. 

There are 2 additional functions from main called customer() and barber(). The customer() function takes care of the customers walking into the barbershop and either take a seat to wait for the barber, take a seat to get a haircut from the barber, or leave the shop if there are no more free chairs. The barber() function implements the actions of the barber when he gets a customer and has to give a haircut. 

When running the program with the command "./sleepybarber" there will be many print statements indicating that a customer takes a seat at the shop, a customer is waking up the barber, a customer is getting a haircut, the barber is taking a customer, and barber is giving a haircut.

The commands that must be used with this program are the following
gcc -o sleepybarber sleepybarber.c -lpthread
./sleepybarber
