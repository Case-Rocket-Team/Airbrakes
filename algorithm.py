# Airbrakes Algorithm
# Written by
# Last Modified: 11/02/2022

def main() -> None:
    """
    This fucntion is the main driver of the whole program,
    organizing the calling sections of the algorithm.

    1. Determine Target Apogee
    2. Call State Estimator
    3. Pass State to Physics Simulator
    4. Take theta deployment from Physics Simulator
    5. Convert theta deployment to motor movement
    6. Repeat

    """
    raise NotImplementedError


def theta_to_motor(theta: float) -> float:
    """
    Converts a theta_deployment for the flap to the required
    motor movement

    :param theta: float
    :return: float
    """

    raise NotImplementedError

    return motor_movement
