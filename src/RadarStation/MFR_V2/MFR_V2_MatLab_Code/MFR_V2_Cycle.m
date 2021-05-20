function [MFR,MSG] = MFR_V2_Cycle(TG,MFR,dT)
    %T for output purposes
    %OUT=[];
    Rsc = TG.R0 + TG.V.*MFR.tsc; %Target coordinates at scan
    dRsc = TG.V.*MFR.Tscan;        %Target movement during single scan
    RscSize = size(Rsc);
    Rloc = repmat(MFR.Loc,RscSize(1),1); %Transition to XYZ coord with MFR at center
    Rsc = Rsc-Rloc;                   %Transition to XYZ coord with MFR at center
    ts = MFR.tsc:MFR.Tscan:dT;            %Scanning time vector

    tsN = length(ts);           %Number of time steps
    pos = mod( (MFR.pos-1) + (0:(tsN-1)),MFR.posN ) + 1; %Scan positions
    sz = size(TG.R0);

    for p=1:length(pos)
        for n=1:sz(1)
            DistTarget = vecnorm(Rsc(n,:)); %Distance to target
            if (MFR.Dmin < DistTarget) && (DistTarget < MFR.Dmax)   %Distance check
                R_p_abs = Rsc(n,:)*MFR.ed(pos(p),:)'; %Length of projection R_p
                R_p = MFR.ed(pos(p),:)*R_p_abs;
                R_n = Rsc(n,:) - R_p;
                CND = ( (R_n*MFR.ee(pos(p),:)') / (R_p_abs*MFR.tge))^2 + ...
                      ( (R_n*MFR.ea(pos(p),:)') / (R_p_abs*MFR.tga))^2;
                if CND <= 1 %Enters scan cone
                    pow_coeff = 1-0.5*CND;  %Affects signal power; <1
                    %Received signal power divided by noise
                    E = MFR.Pc*pow_coeff*TG.RCS(n)/(Rsc(n,:)*Rsc(n,:)')^2;  
                    if E > MFR.Tr
                        %Detected
                        Lia = ismember(TG.ID(n),MFR.tgID);
                        if ~Lia
                            [Lia,Locb] = ismember(0,MFR.tgID);
                            if Lia
                                MFR.tgID(Locb) = TG.ID(n);
                            end
                        end
                        %OUT = [OUT; Rsc(n,:) + MFR.Loc];
                    end
                end
            end
        end
        Rsc = Rsc+dRsc;

    end


    %Checking position of tracked targets at time T+dt
    TrackedID = nonzeros(MFR.tgID);
    [~,index] = ismember(TrackedID,TG.ID);
    RscTracked = TG.R0(index,:) + TG.V(index,:).*dT;
    RscSizeTR = size(RscTracked);
    RlocTR = repmat(MFR.Loc,RscSizeTR(1),1); %Transition to XYZ coord with MFR at center
    Nrm = vecnorm(RscTracked-RlocTR,2,2); %Distance to target
    TrackedIDcheck = (MFR.Dmin < Nrm) & (MFR.Dmax > Nrm);   %Distance check
    TrackedIDnext = nonzeros(TrackedIDcheck.*TrackedID);    %Trackable ID

    %Check for lost targets and their removal from the table MFR.tgID
    TrackedIDlost = nonzeros(~TrackedIDcheck.*TrackedID);  %Lost targets

    [~,index] = ismember(TrackedIDlost,MFR.tgID);
    MFR.tgID(index) = 0 ;  %removal

    %Get tracked target's coordinates; 
    [~,index] = ismember(TrackedIDnext,TrackedID);
    RscTracked = RscTracked(index,:);  %Tracked coordinates
    VscTracked = TG.V(index,:);        %Tracked speed
    

    
    %[~,IDtoRow]=ismember(TrackedIDnew,MFR.tgID);
    %MFR.tgID = zeros(size(MFR.tgID));
    %MFR.tgID(IDtoRow) = TrackedIDnew;    %Table of tracked targets
    MFR.tsc = mod(ts(end)+MFR.Tscan,dT);  %Next scan time deviation
    MFR.pos = pos(end)+1;                 %Next cycle start
    
    %Check for new targets
    flag = ~ismember(TrackedIDnext,MFR.tgIDprev);
    index = find(flag);
    TrackedIDnew = TrackedIDnext(index);
    
    [~,MSG_IDLost] = ismember(TrackedIDlost,MFR.tgIDprev);
    [~,MSG_IDNew] = ismember(TrackedIDnew,MFR.tgID);
    [~,MSG_IDTracked] = ismember(TrackedIDnext,MFR.tgID);

    %Tracked ID, R,V

    MSG = struct(...
        'IDLost', nonzeros(MSG_IDLost),...
        'IDNew', nonzeros(MSG_IDNew),...
        'IDTracked', nonzeros(MSG_IDTracked),...
        'RTrackedX', RscTracked(:,1), ...
        'RTrackedY', RscTracked(:,2), ...
        'RTrackedZ', RscTracked(:,3), ...
        'VTrackedX', VscTracked(:,1), ...
        'VTrackedY', VscTracked(:,2), ...
        'VTrackedZ', VscTracked(:,3));

 
    MFR.tgIDprev = TrackedIDnext; %for the next cycle
    %Output to PBU
%     disp(['!!!---Time T=' num2str(T)]);
%     if ~isempty(TrackedIDlost)
%         disp(['!-Targets ID=[' num2str(TrackedIDlost(:)') '] lost']);
%     end
%     if ~isempty(TrackedIDnew)
%         disp(['!-New targets ID=[' num2str(TrackedIDnew(:)') '] detected']);
%     end
%     for n=1:length(TrackedIDnext)
%         disp(['Target ID:' num2str(TrackedIDnext(n)) '  Coordinates [' num2str(RscTracked(n,:)) ']']);
%     end
end