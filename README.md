# Airbrakes

This contains code to drive the Airbreaks project for Case Rocket Team.

```mermaid
graph TD;
    Main_Algorithm-->State_Estimator;
    Theta_D_vs_Motor_Movement-->Main_Algorithm;
    State_Estimator-->Angle_Optimizer;
    Angle_Optimizer-->Physics_Sim;
    Physics_Sim-->Angle_Optimizer;
    Angle_Optimizer-->Main_Algorithm;
    Coeff_Drag_Lookup-->Physics_Sim;
    Main_Simulation-->Main_Algorithm;
    Main_Algorithm-->Main_Simulation;
    Monte_Carlo-->Main_Simulation;
```


Using the HiLetgo BTS7960 for now...

Progress on Arduino:
1. Figured out how to control the motor. Clockwise and CounterClockwise. 
