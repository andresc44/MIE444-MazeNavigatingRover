% Copyright (c) 2020, Ian G. Bennett
% All rights reserved.
% Development funded by the University of Toronto, Department of Mechanical
% and Industrial Engineering.
% Distributed under GNU AGPLv3 license.

clear
close all
clc

sim = 1;

if sim
    % Initialize tcp server to read and respond to algorithm commands
    [s_cmd, s_rply] = tcp_setup();
    fopen(s_cmd);
    %fopen(s_rply);
else
    % connect to Bluetooth
    btInfo = instrhwinfo('Bluetooth','ROB6')
    s_cmd = Bluetooth(btInfo.RemoteID, 1);
    fopen(s_cmd);
    s_rply = s_cmd;
end

% Robot Sensor Measurements
u = [0,0,0,0,0,0];  % Ultrasonic measurements
pos = [0,0,0];  % Position (x,y,rotation)
speed = 2;
rot_stuck = 90;
stepcount = 0;

while 1
    
    % Take Measurements
    %for ct = 1:6
    %    cmdstring = [strcat('u',num2str(ct)) newline];
    %    u(ct) = tcpclient_write(cmdstring, s_cmd, s_rply);
    %end
    
    cmdstring = ['ua' newline];
    u = tcpclient_write(cmdstring, s_cmd, s_rply);
    
    %ir = tcpclient_write(['i1' newline], s_cmd, s_rply);
    
    %comp = tcpclient_write(['c1' newline], s_cmd, s_rply);
    
    % Display Values
    disp('Ultrasonic')
    disp(u)
    
    if  (u(1) > 4) && (u(2) > 2.5) && (u(5) > 2.5) && (u(4) > 2.5)

        % If the way ahead is clear, go forward
        cmdstring = [strcat('d1-',num2str(speed)) newline];             % Build command string to move bot
        reply = tcpclient_write(cmdstring, s_cmd, s_rply);
        disp("1")
        
    elseif (u(2) > u(5)) && (u(2) > 4)

        % If not, pick a random direction that is clear and go that way
        cmdstring = [strcat('r1-',num2str(30)) newline];  % Build command string to rotate bot
        reply = tcpclient_write(cmdstring, s_cmd, s_rply);
        disp("2")
        
    else
        % If not, pick a random direction that is clear and go that way
        cmdstring = [strcat('r1-',num2str(-30)) newline];  % Build command string to rotate bot
        reply = tcpclient_write(cmdstring, s_cmd, s_rply);
        disp("3")
        
    end
    
    stepcount = stepcount+1;
end