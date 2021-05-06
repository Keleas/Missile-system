function RadarParametresEvaluation(lambda,D,         ...
                                   tau,BwC,BPC,K,Tr, ...
                                   RCST,PrbF,        ...
                                   a,b,g,            ...
                                   eps1,eps2,        ...
                                   Ntraj)
    arguments
        %Base parametres:
        lambda (1,1) {mustBePositive,mustBeFinite} = 30      %wavelength, mm
        D      (1,1) {mustBePositive,mustBeFinite} = 100    %Maximum scanning distance, km
        %Receiving path parametres:
        tau    (1,1) {mustBePositive,mustBeFinite} = 0.05   %Simple signal timewidth, ms
        BwC    (1,1) {mustBePositive,mustBeFinite} = 40      %Bandwidth coefficient
        BPC    (1,1) {mustBePositive,mustBeFinite} = 1.1    %Blanking pulse time coefficient
        K      (1,1) {mustBePositive,mustBeFinite} = 1.1    %Noise factor
        Tr     (1,1) {mustBePositive,mustBeFinite,mustBeGreaterThan(Tr,1)} = 6 ...
            %Detection threshold divided by noise
        %Template target parametres:
        RCST   (1,1) {mustBePositive,mustBeFinite} = 5    %RCS of a template target
        PrbF   (1,1) {mustBePositive,mustBeFinite,mustBeLessThan(PrbF,1)} = 0.001  ...
            %Probablity of false alarm target detection at range D
        %Radar dish:
        a      (1,1) {mustBePositive,mustBeFinite} = 3.5    %Radar height, m
        b      (1,1) {mustBePositive,mustBeFinite} = 2.5    %Radar width, m
        g      (1,1) {mustBePositive,mustBeFinite,mustBeLessThan(g,1)} = 0.8      ...
            %Radar effectivness
        eps1   (1,1) {mustBeFinite} = 0     %Angle of elevation min (deg)
        eps2   (1,1) {mustBeFinite} = 30      %Angle of elevation max (deg)
        
        Ntraj  (1,1) {mustBePositive,mustBeFinite,mustBeInteger} = 64 % Fmount of trackable targets
    end
    %Constants
    c = 299792458; %speed of light m/s
    k = 1.380639*10^(-23); %Boltzmann constant J/K
    
    D = D*1000; %D in metres
    tau = tau*0.001; %tau in sec
    lambda = lambda/1000; %lambda in metres
    eps1 = eps1/180*pi; %eps1 in radians
    eps2 = eps2/180*pi; %eps1 in radians
    
    %Scanning time
    T = 2*D/c;
    %Bandwidth
    df  = BwC/tau/2;
    %Target speed limit
    v = lambda*df/4;
    %Min range
    d = c*tau*BPC/2;
    %Angle resolution
    beta = 2*asin(0.887*lambda/b);
    eps = 2*asin(0.887*lambda/a);
    %Antenna gain
    G=4*pi/eps/beta*g;
    %Noise strength
    N = k*df*290*K;
    %Minimal signal energy on the receiveng path
    Emin = 2*N*Tr^2/(norminv(PrbF))^2;
    %Target drop-out probability
    Pdo = normcdf( (Tr*N/Emin-1)*sqrt(2*Emin/N) );
    %Output energy
    Eout = (4*pi)^3*D^4/(G*lambda)^2/RCST*Emin;
    %Peak Output power
    Ppk = Eout/tau;
    %Average output power
    Pav = Eout/T;
    %Scan time
    Neps  = ceil((eps2-eps1)/eps);
    Nbeta = ceil(2*pi/beta);
    if ~mod(Nbeta,2)
        Nbeta =Nbeta+1;
    end
    Tsc = Neps*Nbeta*T;
    
    %Output
    disp("Scanning time (ms):");
    disp(T*1000);
    disp("Bandwidth (MHz):");
    disp(df/1000000);
    disp("Min range (km):");
    disp(d/1000);
    
    disp("Asimuth antenna pattern resolution (deg):");
    disp(beta*180/pi);
    disp("Angle of elevation antenna pattern resolution (deg):");
    disp(eps*180/pi);
    disp("Antenna gain");
    disp(G);
    
    disp("Noise strength (J):");
    disp(N);
    disp("Minimal impulse energy (J):");
    disp(Emin);
    disp("Target drop-out probability");
    disp(Pdo);
    disp("Output impulse energy (J):");
    disp(Eout);
    disp("Peak output power (MW):");
    disp(Ppk/1000000);
    disp("Average output power (MW):")
    disp(Pav/1000000);
    disp("Scan time (sec):");
    disp(Tsc);
    
    disp("Target speed limit(m/sec)");
    disp(v);
    
    %Output into file
    %Wavelength
    MFR.lambda = lambda;
    %Scanning distance
    MFR.Dmax = D;
    MFR.Dmin = d;
    %Signal form
    MFR.Tscan = T;
    MFR.Timp = tau;
    MFR.asim = beta;
    MFR.elev = eps;
    %Receiver/Transmitter
    MFR.Bandwidth = df;
    MFR.Noise = N;
    MFR.Gain = G;
    MFR.P = Ppk;
    MFR.Tr = Tr;
    %Scanning limits
    MFR.elev1 = min([eps1 eps2]);
    MFR.elev2 = max([eps1 eps2]);
    MFR.Nasim = Nbeta; %amount of asimuth points
    MFR.Nelev = Neps;  %amount of angle of elevation points
    MFR.Ntraj = Ntraj; %Number of traceable trajectories
    
    save('MFR.mat','MFR');
end