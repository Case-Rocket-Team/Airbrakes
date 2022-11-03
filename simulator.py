# Simulation Code
# Written by
# Last Modified: 11/02/2022

# Taken from: https://www.codesansar.com/numerical-methods/secant-method-python-program.htm
# Implementing Secant Method
def secant(x0: float, x1: float, e: float, N: int) -> float:
    """"
    Implements secant method on f(x)

    :param x0: float
    :param x1: float
    :param e: float
    :param N: float
    :return: float
    """

    print('\n\n*** SECANT METHOD IMPLEMENTATION ***')
    step = 1
    low_error = False
    while not low_error:
        if f(x0) == f(x1):
            print('Divide by zero error!')
            break

        x2 = x0 - (x1 - x0) * f(x0) / (f(x1) - f(x0))
        print('Iteration-%d, x2 = %0.6f and f(x2) = %0.6f' % (step, x2, f(x2)))
        x0 = x1
        x1 = x2
        step = step + 1

        if step > N:
            print('Not Convergent!')
            break

        low_error = abs(f(x2)) < e
    print('\n Required root is: %0.8f' % x2)
    return x2

# Defining Function
def f(x):
    return x ** 3 - 5 * x - 9

def test_secant():
    """"
    Test of secant method
    """
    # Input Section
    x0 = input('Enter First Guess: ')
    x1 = input('Enter Second Guess: ')
    e = input('Tolerable Error: ')
    N = input('Maximum Step: ')

    # Converting x0 and e to float
    x0 = float(x0)
    x1 = float(x1)
    e = float(e)

    # Converting N to integer
    N = int(N)

    # Note: You can combine above three section like this
    # x0 = float(input('Enter First Guess: '))
    # x1 = float(input('Enter Second Guess: '))
    # e = float(input('Tolerable Error: '))
    # N = int(input('Maximum Step: '))

    # Starting Secant Method
    secant(x0, x1, e, N)


def simulation(altitude: float, theta_D: float) -> float:
    """
    simulates a rocket from current altitude to apogee

    :param altitude: float
    :param theta_D: float
    :return: float
    """

    raise NotImplementedError

    return apogee


def simulate_step(altitude:float, theta_D: float, t: float) -> float:
    """
    simulates a single step of time

    :param altitude: float
    :param theta_D: float
    :param t: float
    :return: float
    """

    raise NotImplementedError

    return altitude

