function [MSG,MFR] = MFR_V2_Radar_output_codegen() %#codegen
    %Does not progress time T!
    rng('shuffle');
    dT=20+rand();  %step in sec
    %Target generation
    n = 3 + round(100*rand()); %number of targets
    TG_ID = (100:(n+99))';
    TG_R0 = (rand([n 3])-0.5).*[ones([n 2])*100 ones([n 1])*10]*1000;
    TG_V = [(rand([n 2])-0.5)*1000 zeros([n 1])];
    TG_RCS = rand([n 1])*10+0.005;
    
    TG_R0X = TG_R0(:,1); TG_R0Y = TG_R0(:,2); TG_R0Z = TG_R0(:,3);
    TG_VX = TG_V(:,1); TG_VY = TG_V(:,2); TG_VZ = TG_V(:,3);
    
    %Radar generation
    Loc = [0 0 100];
    n = [0 0 1];
    lambda = 0.0300;
    Dmax = 100000;
    Dmin = 8.2443e+03;
    Tscan = 6.6713e-04;
    Timp = 5.0000e-05;
    V_res = 20;
    asim_res = 0.0213;
    elev_res = 0.0152;
    asim_res_trace_cf = 0.1000;
    elev_res_trace_cf = 0.1000;
    elev1 = 0;
    elev2 =0.5236;
    Nasim = 297;
    Nelev = 35;
    Bandwidth = 400000;
    Noise = 1.7617e-15;
    Gain = 3.1056e+04;
    P_peak = 1.2146e+07;
    Tr = 6;
    Ntraj = 64;
    Nmissiles = 64;

    %Runs once (initialization)
    MFR = MFR_V2_GenerateMFRType(...
        Loc, n,...
        lambda, Dmax, Dmin, Tscan, Timp, V_res,...
        asim_res, elev_res, asim_res_trace_cf, elev_res_trace_cf,...
        elev1, elev2, Nasim, Nelev, ...
        Bandwidth, Noise, Gain, P_peak, Tr,...
        Ntraj,Nmissiles);

    %Runs in cycle
    TG = MFR_V2_GenerateTrajectoryType(TG_ID, TG_R0X, TG_R0Y, TG_R0Z, ...
                                       TG_VX, TG_VY, TG_VZ, TG_RCS);      %Format for trajectory input
    [MFR,MSG] = MFR_V2_Cycle(TG,MFR,dT);
end



