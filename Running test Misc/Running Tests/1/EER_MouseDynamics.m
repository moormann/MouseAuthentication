function EER_MouseDynamics()

 fid = fopen('EER.txt', 'w');
 imposId = fopen('imposNameFile.txt');
 legitId = fopen('legitNameFile.txt');

 imposName = fgetl(imposId);
 legitName = fgetl(legitId);
 
 firLowestFN = 'None';
 secLowestFN = 'None';
 thiLowestFN = 'None';

 firLowest = 1;
 secLowest = 1;
 thiLowest = 1;
 
while ~feof(imposId)
 
 false_scoreS_750=load(imposName);
 true_scoresS_750=load(legitName);


FRR_S_750=0;
IPR_S_750=0;

 
IPR_S_750_ex=0;



 d_S_750=size(true_scoresS_750);


 d_IPR_S750=size(false_scoreS_750);

n_S=1;
for (i_S=0:0.001:1)
   
    FRR_S_750=0;
    IPR_S_750=0;
    
  
    IPR_S_750_ex=0;
    
    
 
    for (m_S=1:d_S_750)
        if(1-true_scoresS_750(m_S)> i_S) % change direction for SIMILARITY
            FRR_S_750=FRR_S_750+1;
        end
    end
    plot_FRR_S_750(n_S,1)=FRR_S_750/d_S_750(1,1);
    
    for (m_S=1:d_IPR_S750)
        if(1-false_scoreS_750(m_S)<= i_S) % change direction for SIMILARITY
            IPR_S_750=IPR_S_750+1;
        end
    end
    plot_IPR_S_750(n_S,1)=IPR_S_750/d_IPR_S750(1,1);


    n_S=n_S+1;
end
 


xaxis=0:0.001:1;

[X0_750,Y0_750] = intersections(xaxis,plot_FRR_S_750,xaxis,plot_IPR_S_750);
EER_750=Y0_750(1);
Threshold_750=1-X0_750(1);
fprintf(fid, 'EER for 750M is: %f, Threshold: %f and for extra is: %f, Threshold: %f\r\n\r\n\r\n', EER_750, Threshold_750);
%plot(0:0.001:1, plot_FRR_S_750, '--',0:0.001:1,plot_IPR_S_750,'r')


if firLowest > EER_750
    thiLowest = secLowest;
    secLowest = firLowest;
    firLowest = EER_750;
    
    thiLowestFN = secLowestFN;
    secLowestFN = firLowestFN;
    firLowestFN = imposName;
elseif secLowest > EER_750
    thiLowest = secLowest;
    secLowest = EER_750;
    
    thiLowestFN = secLowestFN;
    secLowestFN = imposName;
elseif thiLowest > EER_750
    thiLowest = EER_750;
    
    thiLowestFN = imposName;
end

fprintf('\n\n\n\n\n\n\n\n\n\n');
fprintf('Lowest: %f  Settings: %s\n',firLowest, firLowestFN);
fprintf('Second : %f  Settings: %s\n',secLowest, secLowestFN);
fprintf('Third  : %f  Settings: %s\n',thiLowest, thiLowestFN);
fprintf('  %s\n', imposName);


 imposName = fgetl(imposId);
 legitName = fgetl(legitId);
 
end
    