clc, clear, close all;
%% Parameters
pwm_max = 255;
wheel_radius = 0.029; %radius of wheel
diam2centre = 0.102; %centre of chassis to mid wheel 102mm
rpm2rps = 2*pi/60; %conversion factor

measured_max_speed_forward = 0.2490;

%true_max_rpm = measured_max_speed_forward/wheel_radius/rpm2rps
%max_rpm = 82; //at no torque, 6V

max_rps = measured_max_speed_forward/wheel_radius
%max_lin_vel = max_rps*wheel_radius
%max_rot_vel = max_lin_vel/diam2centre




%% Input
orig_speeds = [measured_max_speed_forward;
          0;
          0;
];
speeds = [-orig_speeds(2);
          orig_speeds(1);
          orig_speeds(3);
]


%% Matrix
%sin(pi/3) = 0.866
transform_M = [-0.5 -0.866 -diam2centre;
               -0.5  0.866 -diam2centre;
                1    0         -diam2centre];

rot_vels = transform_M*speeds %m/s
rad_vels = rot_vels./wheel_radius %rad/s
pwms = rad_vels./max_rps.*pwm_max

M2 = transform_M./wheel_radius./max_rps.*pwm_max


pwms2 = M2*speeds




%motor_speeds = round(pwm_max.*transform_M*direction);








% motor_forward_angles_x = [cos(240*pi/180); cos(120*pi/180); cos(0*pi/180)];
% motor_forward_angles_y = [sin(240*pi/180); sin(120*pi/180); sin(0*pi/180)];
% 
% vector = horzcat(motor_forward_angles_x.*motor_speeds, motor_forward_angles_y.*motor_speeds);
% denom = 3*255;
% 
% A = [vector(1,1), vector(1,2)]./denom;
% B = [A(1) + vector(2,1)./denom, A(2)+vector(2,2)./denom];
% C = [B(1) + vector(3,1)./denom, B(2)+vector(3,2)./denom];
% 
% plot([0,A(1)], [0, A(2)], 'r', 'LineWidth', 2);
% hold on
% plot([A(1),B(1)], [A(2), B(2)], 'b', 'LineWidth', 2);
% hold on
% plot([B(1),C(1)], [B(2), C(2)], 'g', 'LineWidth', 2);
% hold on
% plot([0,C(1)], [0, C(2)], '--k', 'LineWidth', 2);
% hold on
% th = 0:pi/50:2*pi;
% xunit = cos(th);
% yunit = sin(th);
% %plot(xunit, yunit);
% grid minor
% lim = max(abs(C))*1.1;
% xlim([-lim,lim])
% ylim([-lim,lim])
% 
% isXpos = C(1) >= 0;
% isYpos = C(2) >= 0;
% final_angle = atan(C(2)/C(1))*180/pi
% 
% if (isYpos && ~isXpos)
%     final_angle = 180+final_angle;
% 
% elseif (~isYpos && ~isXpos)
%     final_angle = 180+final_angle;
% 
% elseif (~isYpos && isXpos)
%     final_angle = 360+final_angle;
% end
% 
% motor_speeds
% final_angle
% power_efficiency = hypot(C(1), C(2))*100



