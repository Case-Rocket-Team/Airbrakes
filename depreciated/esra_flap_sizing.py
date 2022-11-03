# Airbrakes Flap Sizing
# Written by Myles Smith
# Last Modified: 5/15/2021

# This script simulates the rocket's flight path during coast and uses Newton's Method to calculate the required flap size. 

import math

vehicle_reference_area =  0.01929 # meters squared 
vehicle_motorless_mass = 20.1 # kg
motor_empty_mass =  3.75 # kg
velocity_at_burnout = 253.4 # m/s 
altitude_at_burnout = 1202.5 # m 
flap_curve_angle = 23 # degrees
rocket_OD = 0.157 # m 
desired_apogee =  3048  # m (10000ft)
openrocket_natural_apogee = 3361 # m
mach_numbers = [0.04, 0.05, 0.1, 0.15, 0.20, 0.25, 0.30, 0.35, 0.40, 0.45, 0.50, 0.55, 0.60, 0.65, 0.70, 0.75, 0.80, 0.85]
cd_values = [0.44, 0.44, 0.44, 0.44, 0.44, 0.45, 0.45, 0.46, 0.46, 0.47, 0.48, 0.48, 0.49, 0.51, 0.52, 0.53, 0.55, 0.57]

vehicle_mass = vehicle_motorless_mass + motor_empty_mass

# calculate flap width
# the flap width can be calculated using the arc length formula: s = 2 * pi * radius * theta / 360
flap_width = math.pi * rocket_OD * flap_curve_angle / 360 # m

def calc_rocket_cd(pre_vel, mach_numbers, cd_values):
    mach_num = pre_vel / 343

    index = 0 
    while mach_numbers[index] < mach_num:
        index = index + 1

    if mach_numbers[index] == mach_num:
        return cd_values[index]

    # we know the mach number is between index -1 and index so we can use linear interpolation
    x1 = mach_numbers[index - 1]
    x2 = mach_numbers[index]
    y1 = cd_values[index - 1]
    y2 = cd_values[index]
    x = mach_num
    y = (y1 * (x2 - x) + y2 * (x - x1)) / (x2 - x1) # cd value
    return y


def calc_rho(pre_alt):
    alt = [0, 500, 1000, 1500, 2000, 2500, 3000, 3500, 4000, 4500, 5000]
    rho_values = [1.225, 1.1673, 1.1117, 1.0591, 1.0066, 0.95695, 0.90912, 0.86323, 0.81913, 0.77677, 0.73612]
    # find the apogee in the array that is just before the previous simulated apogee
    i = 0 
    while alt[i] < pre_alt:
        i = i + 1
    
    if alt[i] == pre_alt:
        return rho_values[i]

    x1 = alt[i - 1]
    x2 = alt[i]
    y1 = rho_values[i - 1]
    y2 = rho_values[i]
    x = pre_alt
    return (y1 * (x2 - x) + y2 * (x - x1)) / (x2 - x1)


def calc_g(pre_alt):
    alt = [0, 1000, 2000, 3000, 4000]
    g_values = [9.807, 9.804, 9.801, 9.797, 9.794]

    i = 0 
    while alt[i] < pre_alt:
        i = i + 1

    if alt[i] == pre_alt:
        return g_values[i]

    x1 = alt[i - 1]
    x2 = alt[i]
    y1 = g_values[i - 1]
    y2 = g_values[i]
    x = pre_alt
    return (y1 * (x2 - x) + y2 * (x - x1)) / (x2 - x1)


def determine_apogee(rocket_area, flap_area, mass, burnout_vel, burnout_alt, mach_numbers, cd_values, flap_width):
    time = 0  # setting time at burnout to 0
    dt = 0.0001  # time step
    vel = [burnout_vel]
    apo = [burnout_alt]
    flap_cd = 0.9114346387

    # drag forces uses the reference area of the flap - not its actual area. 
    # we are given its actual area, and it's width, so from that we can calculate its height.
    # using trig, we can get its reference area
    one_flap_area = flap_area / 4
    flap_height = one_flap_area / flap_width
    one_flap_ref_area = flap_height * math.sin(40 * math.pi / 180) * flap_width
    flaps_ref_area = one_flap_ref_area * 4

    # at apogee the velocity is zero, so the loop will run until the rocket has reached apogee
    while vel[-1] > 0:
        rho = calc_rho(apo[-1] + 1401)
        
        g = calc_g(apo[-1])

        # Using Newton's second law: F = ma, we know that a = F/m. The forces acting on the rocket are drag and gravity.
        # The total drag force is the rocket drag plus the flaps drag (each with their own area and Cd) 
        # The rocket's Cd varries with velocity, whereas the flap Cd is constant.
        # drag force = 0.5 * rho * reference area * drag coefficient * (velocity squared)
        rocket_cd = calc_rocket_cd(vel[-1], mach_numbers, cd_values)
        rocket_drag = 0.5 * rho * rocket_area * rocket_cd * (vel[-1] ** 2)
        flap_drag = 0.5 * rho * flaps_ref_area * flap_cd * (vel[-1] ** 2)
        total_drag_force = rocket_drag + flap_drag
        acceleration = (-1 * mass * g - total_drag_force) / mass

        # From the kinematics equations:
        velocity = vel[-1] + acceleration * dt
        vel.append(velocity)

        apogee = apo[-1] + velocity * dt + 0.5 * acceleration * (dt ** 2)
        apo.append(apogee)
        # We are using dt for time in the kinematic equations because it is an iterative process

        time = time + dt

    return apogee


def calculate_flap_size(ref_area, mass, burnout_vel, burnout_alt, target_apo, OD, mach_numbers, cd_values, flap_width):
    # x is the total reference area and f is the simulated apogee
    x = []
    f = []

    # first step in Newton's method is to get the two starting points
    # the first point will be the given reference area of just the rocket without flaps because it is smaller than the area with flaps
    x1 = 0
    y1 = determine_apogee(ref_area, x1, mass, burnout_vel, burnout_alt, mach_numbers, cd_values, flap_width)
    y1 = y1 - target_apo # adjust reference frame
    x.append(x1)
    f.append(y1)

    # the second point is arbitrarily choosen. We can assume the area of one flap will not be more than 5in^2, so 20in^2 for four flaps.
    x2 = 20 * 0.0254 * 0.0254 # reference area of the rocket without flaps and a likely maximum flap area
    y2 = determine_apogee(ref_area, x2, mass, burnout_vel, burnout_alt, mach_numbers, cd_values, flap_width)
    y2 = y2 - target_apo # adjust reference frame
    x.append(x2)
    f.append(y2)

    criteria = 0.05
    convergence = criteria + 1 # starts the loop
    count = 0
    
    # uses the area of the flap not it's reference area
    while convergence > criteria:
        next_flap_area = x[-1] - f[-1] * ((x[-1] - x[-2]) / (f[-1] - f[-2])) # secant method    

        next_apo = determine_apogee(ref_area, next_flap_area, mass, burnout_vel, burnout_alt, mach_numbers, cd_values, flap_width)
        next_apo = next_apo - target_apo # adjust reference frame

        convergence = abs((x[-1] - x[-2]) / x[-1])

        x.append(next_flap_area)
        f.append(next_apo)
        count = count + 1

    final_simulated_apo = f[-1] + target_apo
    print('Final Simulated Apogee:', final_simulated_apo, 'm')
    print('Count:', count)
    
    # we know the flaps need to cover the area found so each flap needs to cover:
    one_flap_area = x[-1] / 4 # meters squared

    # we know the width of the flap and the area, so the height can be found:
    height = one_flap_area / flap_width # m
    one_flap_area = one_flap_area * 39.37008 * 39.37008 # m squared to inches squared
    print('Area of one flap:', one_flap_area, 'in^2')
    height = height * 39.37008 # m to inches
    print('Flap Height:', height, 'in')
    flap_width = flap_width * 39.37008 # m to inches
    print('Flap width:', flap_width, 'in')


def main():
    print('openrocket natural apogee', openrocket_natural_apogee, 'm')
    simulated_natural_apogee = determine_apogee(vehicle_reference_area, 0, vehicle_mass, velocity_at_burnout, altitude_at_burnout, mach_numbers, cd_values, flap_width)
    print('simulated natural apogee:', simulated_natural_apogee, 'm')
    percent_error = abs((openrocket_natural_apogee - simulated_natural_apogee) / openrocket_natural_apogee) * 100
    print('percent error', percent_error, '%')
    print('Target Apogee:', desired_apogee, 'm')
    calculate_flap_size(vehicle_reference_area, vehicle_mass, velocity_at_burnout, altitude_at_burnout, desired_apogee, rocket_OD, mach_numbers, cd_values, flap_width)
    

if __name__ == "__main__":
    main()


# air density value source: https://apps.dtic.mil/dtic/tr/fulltext/u2/a035728.pdf