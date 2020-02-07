%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Matlab example for communication with a GSV-8                              %
% (the function requires MinGW-W64 C/C++ compiler package)                   % 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%% define the COM Port
com = 3;
% load MEGSV Dynamic Link Library   MEGSV86x64.dll & MEGSV86x64.h for 64bit or
% MEGSV86w32.dll & MEGSV86w32.h for 32bit

if ~libisloaded('MEGSV86x64')
   loadlibrary('.\MEGSV86x64.DLL','.\MEGSV86x64.h')
end
% activate channel
[extendet] = calllib('MEGSV86x64','GSV86actExt',com);  
calllib('MEGSV86x64','GSV86startTX',com);

% setting the sampling rate
calllib('MEGSV86x64','GSV86setFrequency',com, 18000); 

%% definition of the variables
x=zeros(1,1); % A Vector filled with Zeros (100x1)
z=int32(0); % A Variable Type Integer32

adx = libpointer('doublePtr',x);
adx2 = libpointer('doublePtr',x);
adx3 = libpointer('doublePtr',x);
adx4 = libpointer('doublePtr',x);
adx5 = libpointer('doublePtr',x);
adx6 = libpointer('doublePtr',x);
% adx7 = libpointer('doublePtr',x);
% adx8 = libpointer('doublePtr',x);

valsread = libpointer('int32Ptr',z);
errorread = libpointer('int32Ptr',z);

h1 = animatedline;
h2 = animatedline;
h3 = animatedline;
h4 = animatedline;
h5 = animatedline;
h6 = animatedline;
% h7 = animatedline;
% h8 = animatedline;

h1.Color = 'black';
h2.Color = 'r';
h3.Color ='y';
h4.Color = 'g';
h5.Color = 'c';
h6.Color = 'b';
% h7.Color = 'm';
% h8.Color = 'y';

fig = gcf;
fig.Color = 'w';

ax = gca;
ax.Color = [1 1 1]; 
ax.YGrid = 'on';
ax.GridColor = [0 0 0];
ax.YLimMode = 'auto';
stop = false;
startTime = datetime('now');

while ~stop
    
    calllib('MEGSV86x64','GSV86clearDeviceBuf',com);
    calllib('MEGSV86x64','GSV86clearDLLbuffer',com);
    pause(0.01);
    [error,data]=calllib('MEGSV86x64','GSV86read',com,1,adx);
    [error2,data2]=calllib('MEGSV86x64','GSV86read',com,2,adx2);
    [error3,data3]=calllib('MEGSV86x64','GSV86read',com,3,adx3);
    [error4,data4]=calllib('MEGSV86x64','GSV86read',com,4,adx4);
    [error5,data5]=calllib('MEGSV86x64','GSV86read',com,5,adx5);
    [error6,data6]=calllib('MEGSV86x64','GSV86read',com,6,adx6); 
    % [error7,data7]=calllib('MEGSV86x64','GSV86read',com,7,adx7);  
    % [error8,data8]=calllib('MEGSV86x64','GSV86read',com,8,adx8);  
    
    t =  datetime('now') - startTime;
    
    addpoints(h1,datenum(t),data)
    addpoints(h2,datenum(t),data2)
    addpoints(h3,datenum(t),data3)
    addpoints(h4,datenum(t),data4)
    addpoints(h5,datenum(t),data5)
    addpoints(h6,datenum(t),data6)
    % addpoints(h7,datenum(t),data7)
    % addpoints(h8,datenum(t),data8)
    
    if (t<seconds(60)) % defines the window time
       ax.XLim = datenum([0 t]); 
    else
       ax.XLim = datenum([t-seconds(60) t]); 
    end
    
    datetick('x','keeplimits')
    drawnow limitrate
end
calllib('MEGSV86x64','GSV86release',com)     % release Channel 
%clear adx valsread
unloadlibrary('MEGSV86x64')            % should be done, but crash Matlab
% % clear all