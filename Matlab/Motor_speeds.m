clc, clear, close all;
%% Input
angle = 69;

%%transform to angle
angle = angle*pi/180;
x_comp = cos(angle);
y_comp = sin(angle);


direction = [x_comp; y_comp];
motor_forward_angles_x = [cos(240*pi/180); cos(120*pi/180); cos(0*pi/180)];
motor_forward_angles_y = [sin(240*pi/180); sin(120*pi/180); sin(0*pi/180)];
pwm_max = 255;
%% Matrix
% leave rotation for later

transform_M = [-1/2 -sin(pi/3);
               -1/2  sin(pi/3);
                1    0         ];
motor_speeds = round(pwm_max.*transform_M*direction);

vector = horzcat(motor_forward_angles_x.*motor_speeds, motor_forward_angles_y.*motor_speeds);
denom = 3*255;

A = [vector(1,1), vector(1,2)]./denom;
B = [A(1) + vector(2,1)./denom, A(2)+vector(2,2)./denom];
C = [B(1) + vector(3,1)./denom, B(2)+vector(3,2)./denom];

plot([0,A(1)], [0, A(2)], 'r', 'LineWidth', 2);
hold on
plot([A(1),B(1)], [A(2), B(2)], 'b', 'LineWidth', 2);
hold on
plot([B(1),C(1)], [B(2), C(2)], 'g', 'LineWidth', 2);
hold on
plot([0,C(1)], [0, C(2)], '--k', 'LineWidth', 2);
hold on
th = 0:pi/50:2*pi;
xunit = cos(th);
yunit = sin(th);
%plot(xunit, yunit);
grid minor
lim = max(abs(C))*1.1;
xlim([-lim,lim])
ylim([-lim,lim])

isXpos = C(1) >= 0;
isYpos = C(2) >= 0;
final_angle = atan(C(2)/C(1))*180/pi

if (isYpos && ~isXpos)
    final_angle = 180+final_angle;

elseif (~isYpos && ~isXpos)
    final_angle = 180+final_angle;

elseif (~isYpos && isXpos)
    final_angle = 360+final_angle;
end

motor_speeds
final_angle
power_efficiency = hypot(C(1), C(2))*100



