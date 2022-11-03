# State Estimator
# Written by
# Last Modified: 11/02/2022

def altitude() -> float:
    """
    Finds the current altitude of the rocket

    :return: float
    """
    return extended_kalman_filter()


def extended_kalman_filter() -> float:
    """
    Implements an extended Kalman filter using a barometer as the source of
    truth while using an accelerometer as short-term change

    :return: float
    """

    raise NotImplementedError

    return altitude
