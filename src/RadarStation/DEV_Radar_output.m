function DEV_Radar_output()
    close all;
    %time
    T=0;    %start
    dT=10;  %step
    T_stop=700; %stop
    %MFR parametres
    LD = load('MFR.mat','MFR');
    MFR = LD.MFR;
    MFR.n = normalize([0 0 1],2,'norm');
    MFR.e = normalize([1 0 0],2, 'norm');
    MFR.p = cross(MFR.n,MFR.e);
    MFR.Loc = [0 0 0.1]*1000;
    SCP = GenerateScanningPattern(MFR);
    %MFR scanning pattern
    
    %Targets
    TG.ID = [7;8;9;10];
    TG.R0=[110  -10  2;...
        110  0  2;...
        110 10  5;...
        110 20  10]*1000;
    TG.V=[-150 0 0;
       -200 0 0;
       -300 0 0;
       -1000 0 0];
    TG.RCS = [1;5;4;10];
   
    Nstep = ceil(T_stop/dT); 
    step = 1;
    R = zeros([size(TG.R0) Nstep] );
    R(:,:,1) = TG.R0;
    sz = size(R);
    OUT = [];

    while T<=T_stop
        %Radar scan
        Rsqueezed = squeeze(R(:,:,step)); %outside data
        Rsc = Rsqueezed + TG.V.*SCP.tsc; %Target coordinates at scan
        dRsc = TG.V.*MFR.Tscan;        %Target movement during single scan
        %RscSize = size(Rsc);
        %Rloc = repmat(MFR.Loc,RscSize(1),1); %Transition to XYZ coord with MFR at center
        Rsc = Rsc-MFR.Loc;                   %Transition to XYZ coord with MFR at center
        ts = SCP.tsc:MFR.Tscan:dT;            %Scanning time vector
        
        tsN = length(ts);           %Number of time steps
        pos = mod( (SCP.pos-1) + (0:(tsN-1)),SCP.posN ) + 1; %Scan positions
        
        
        for p=1:length(pos)
            for n=1:sz(1)
                DistTarget = vecnorm(Rsc(n,:)); %Distance to target
                if (MFR.Dmin < DistTarget) && (DistTarget < MFR.Dmax)   %Distance check
                    R_p_abs = Rsc(n,:)*SCP.ed(pos(p),:)'; %Length of projection R_p
                    R_p = SCP.ed(pos(p),:)*R_p_abs;
                    R_n = Rsc(n,:) - R_p;
                    CND = ( (R_n*SCP.ee(pos(p),:)') / (R_p_abs*SCP.tge))^2 + ...
                          ( (R_n*SCP.ea(pos(p),:)') / (R_p_abs*SCP.tga))^2;
                    if CND <= 1 %Enters scan cone
                        pow_coeff = 1-0.5*CND;  %Affects signal power; <1
                        %Received signal power divided by noise
                        E = SCP.Pc*pow_coeff*TG.RCS(n)/(Rsc(n,:)*Rsc(n,:)')^2;  
                        if E > MFR.Tr
                            %Detected
                            Lia = ismember(TG.ID(n),SCP.tgID);
                            if ~Lia
                                [Lia,Locb] = ismember(0,SCP.tgID);
                                if Lia
                                    SCP.tgID(Locb) = TG.ID(n);
                                end
                            end
                            OUT = [OUT; Rsc(n,:) + MFR.Loc];
                        end
                    end
                end
            end
            Rsc = Rsc+dRsc;
            
        end
        

        %Checking position of tracked targets at time T+dt
        TrackedID = nonzeros(SCP.tgID);
        [~,index] = ismember(TrackedID,TG.ID);
        RscTracked = Rsqueezed(index,:) + TG.V(index,:).*dT;
        Nrm = vecnorm(RscTracked-MFR.Loc,2,2); %Distance to target
        TrackedIDcheck = (MFR.Dmin < Nrm) & (MFR.Dmax > Nrm);   %Distance check
        TrackedIDnew = nonzeros(TrackedIDcheck.*TrackedID);    %Trackable ID
        
        %Check for lost targets and their removal from the table SCP.tgID
        TrackedIDlost = nonzeros(~TrackedIDcheck.*TrackedID);  %Lost targets

        [~,index] = ismember(TrackedIDlost,SCP.tgID);
        SCP.tgID(index) = 0 ;  %removal
        
        %Get tracked target's coordinates; 
        [~,index] = ismember(TrackedIDnew,TrackedID);
        RscTracked = RscTracked(index,:);  %Tracked coordinates
        IDTracked = TrackedIDnew;          %Tracked ID
        %Output to PBU
        disp(['!!!---Time T=' num2str(T)]);
        if ~isempty(TrackedIDlost)
            disp(['!!!---Targets ID=[' num2str(TrackedIDlost) '] lost']);
        end
        for n=1:length(IDTracked)
            disp(['Target ID:' num2str(IDTracked(n)) '  Coordinates [' num2str(RscTracked(n,:)) ']']);
        end
        %[~,IDtoRow]=ismember(TrackedIDnew,SCP.tgID);
        %SCP.tgID = zeros(size(SCP.tgID));
        %SCP.tgID(IDtoRow) = TrackedIDnew;                      %Table of tracked targets
        %System evolution
        T = T+dT;
        
        %Target evolution
        step = step+1;        
        R(:,:,step) = R(:,:,step-1)+TG.V*dT;
        SCP.tsc = mod(ts(end)+MFR.Tscan,dT);  %Next scan time deviation
        SCP.pos = pos(end)+1;
    end
    
    
    %Output;
    figure(1);
    
    for n=1:sz(1)
        X = R(n,1,:)/1000;
        Y = R(n,2,:)/1000;
        Z = R(n,3,:)/1000;
        plot3(X(:),Y(:),Z(:));
        hold on;
    end
    if ~isempty(OUT)
        OUT=OUT/1000;
        scatter3(OUT(:,1),OUT(:,2),OUT(:,3),'.');
    end
    title('Target trajectory');
    grid on;
    xlim([-150 150]);
    ylim([-150 150]);
    %zlim([120*tan(MFR.elev1) 120*tan(MFR.elev2)]);
    zlim([0 20]);
    daspect([1 1 1]);
    
    figure(2);
    plot3(SCP.ed(:,1),SCP.ed(:,2),SCP.ed(:,3));
    daspect([1 1 1]);
    grid on;
    title("Scanning method");
    
%     disp('Radar parameteres:');
%     disp(MFR);
    %disp('Target ID:');
    %disp(SCP.tgID);
    %disp(TrackedIDnew);
end

function SCP = GenerateScanningPattern(MFR)
    %Calculation of coord transition matrix LOCXYZ->GLOBXYZ
    SCP.A = inv([MFR.e' MFR.p' MFR.n'])';
    %Asimuth and elevation angles
    elev = linspace(MFR.elev1 + MFR.elev/2,...
                    MFR.elev2 - MFR.elev/2,...
                    MFR.Nelev)';
    asim = linspace(0,2*pi,MFR.Nasim+1);
    asim = asim(1:end-1);
    SCP.elev = repmat(elev,1,length(asim)); %SCP - scanning pattern

    for n=2:2:length(asim)
        SCP.elev(:,n) = flip(SCP.elev(:,n));
    end
    SCP.asim = repmat(asim,length(elev),1);
    SCP.elev = SCP.elev(:);
    SCP.asim = SCP.asim(:);
    SCP.ed = [cos(SCP.elev).*cos(SCP.asim),...
              cos(SCP.elev).*sin(SCP.asim),...
              sin(SCP.elev)]*SCP.A;
    SCP.ee = [SCP.ed(:,1),...
              SCP.ed(:,2),...
              -( SCP.ed(:,1).^2 + SCP.ed(:,2).^2 )./SCP.ed(:,3)] *SCP.A;
    SCP.ee = normalize(SCP.ee,2,'norm');
    SCP.ea = cross(SCP.ed,SCP.ee,2);
    %Scan start
    SCP.tsc = 0; %Current scan time deviation
    SCP.pos = 1; %Current scan vector number (correlates with .tsc)
    SCP.posN = length(SCP.asim); %number of positions
    %Scan parametres
    SCP.tge = tan(MFR.elev/2);
    SCP.tga = tan(MFR.asim/2);
    SCP.Pc = MFR.P*MFR.Timp*(MFR.Gain*MFR.lambda)^2/(4*pi)^3/MFR.Noise;
    %Scan output
    SCP.tgID = zeros([MFR.Ntraj 1]);
end
