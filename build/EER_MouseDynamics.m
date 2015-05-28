function EER_MouseDynamics()

 fid = fopen('EER.txt', 'w');
 imposId = fopen('Impos.txt');
 legitId = fopen('Legit.txt');


 
 firLowestFN = 'None';
 secLowestFN = 'None';
 thiLowestFN = 'None';

 firLowest = 1;
 secLowest = 1;
 thiLowest = 1;
 
 false_scoreS_750=load('Impos.txt');
 true_scoresS_750=load('Legit.txt');


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
plot(0:0.001:1, plot_FRR_S_750, '--',0:0.001:1,plot_IPR_S_750,'r')



fprintf('\n\n\n\n\n\n\n\n\n\n');
fprintf('%f', EER_750);



end
    