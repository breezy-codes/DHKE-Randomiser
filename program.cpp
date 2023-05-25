#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

// program to implement the diffie hellman key exchange algorithm

// Function to check if a number is prime
bool is_prime(int number)
{
    int i;
    for (i = 2; i <= sqrt(number); i++)
    {
        if (number % i == 0)
            return false;
    }
    return true;
}

// function to generate a random prime number
int generate_random_prime(int min, int max)
{
    int prime;
    do
    {
        prime = (rand() % (max - min + 1)) + min;
    } while (!is_prime(prime));
    return prime;
}

// Function to calculate the power modulo
int power_modulo(int base, int exponent, int modulus)
{
    if (exponent == 0)
        return 1;

    long long result = 1;
    long long power = base % modulus;

    while (exponent > 0)
    {
        if (exponent % 2 == 1)
        {
            result = (result * power) % modulus;
        }
        power = (power * power) % modulus;
        exponent /= 2;
    }
    return static_cast<int>(result);
}

// Function to calculate the primitive root
int calculate_primitive_root(int prime)
{
    int phi = prime - 1;
    std::vector<int> factors;

    // Factorize phi
    int temp = phi;
    for (int i = 2; i * i <= temp; i++)
    {
        if (temp % i == 0)
        {
            factors.push_back(i);
            while (temp % i == 0)
                temp /= i;
        }
    }
    if (temp > 1)
        factors.push_back(temp);

    // Check each value for primitive root property
    for (int root = prime - 1; root > 1; root--)
    {
        bool is_primitive = true;
        for (int factor : factors)
        {
            if (power_modulo(root, phi / factor, prime) == 1)
            {
                is_primitive = false;
                break;
            }
        }
        if (is_primitive)
            return root;
    }
    return -1; // No primitive root found
}

// function to calculate the modular exponentiation
int calculate_modular_exponentiation(int base, int exponent, int mod)
{
    int result = 1;
    while (exponent > 0)
    {
        if (exponent % 2 == 1)
        {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exponent = exponent / 2;
    }
    return result;
}

int main()
{
    cout << "Diffie-Hellman Key Exchange Algorithm" << endl;
    cout << "------- Declaring the inputs -------" << endl;
    // Generate a random prime number
    srand(static_cast<unsigned int>(time(0)));
    int min = 5000;
    int max = 15000;
    int prime = generate_random_prime(min, max);
    cout << "The prime number is: " << prime << endl;

    // calculate the primitive root
    int primitive_root = calculate_primitive_root(prime);
    cout << "The primitive root is: " << primitive_root << endl;

    // Generate the private key for the two parties
    int private_key_A = rand() % (prime - 2) + 1;
    int private_key_B = rand() % (prime - 2) + 1;
    cout << "The private key for A is: " << private_key_A << endl;
    cout << "The private key for B is: " << private_key_B << endl;

    // run the Diffie-Hellman key exchange algorithm
    cout << "------- Running the algorithm -------" << endl;
    int public_key_A = calculate_modular_exponentiation(primitive_root, private_key_A, prime);
    int public_key_B = calculate_modular_exponentiation(primitive_root, private_key_B, prime);
    cout << "---- Calculating the public keys ----" << endl;
    cout << "The public key for A is: " << public_key_A << endl;
    cout << "The public key for B is: " << public_key_B << endl;

    // calculate the shared secret key
    int shared_secret_key_A = calculate_modular_exponentiation(public_key_B, private_key_A, prime);
    int shared_secret_key_B = calculate_modular_exponentiation(public_key_A, private_key_B, prime);
    cout << "- Calculating the shared secret key -" << endl;
    cout << "The shared secret key for A is: " << shared_secret_key_A << endl;
    cout << "The shared secret key for B is: " << shared_secret_key_B << endl;

    return 0;
}
