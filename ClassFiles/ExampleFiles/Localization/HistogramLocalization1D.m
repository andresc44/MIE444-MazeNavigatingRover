function [] = HistogramLocalization1D

locationindex = [1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20];
world =         [1 0 1 1 0 1 0 1 1  1  0  1  0  1  1  0  0  1  1  0];  %1=white 0=black

n = length(world);
p = ones(1,n)*(1/n); %initial probability

measurement =  [1 0 1 1 0 1 0 1 1  1  0  1  0  1  1  0]; %good example
%measurement =  [1 0 0 1 0 1 0 1 1  1  0  1  0  1  1  0]; %bad example
%measurement =  [1 0 0 1 1 1 0 1 1  1  0  1  0  1  1  0]; %bad example
%measurement =  [1 0 1 1 1 0 1 0 1 1  1  0  1  0  1  1  0]; %good example

plot(p); title('Initialization'); ylim([0 0.5]); pause;
    %iteration
    for k = 1:length(measurement),
    
    %sense (load measurment)
    SenVal = measurement(k);
    
    %calculate p based on measurment
    p = sense(world, p, SenVal);
    
    plot(p); title(['step: ' num2str(k)]); ylim([0 0.5]); pause;
      
    %move robot one block (assume this happens in sim without sending the
    %actual command)
    
    %calculate p based on robot moving one block
    p = move(p);
    plot(p); title(['step: ' num2str(k)]); ylim([0 0.5]); pause;
    
    end
end

function pnew = sense(world, p, SenVal)
  pHit = 0.6;
  pMiss = 0.2;  
  pnew = abs(world -(1-SenVal))*pHit + abs(world-(SenVal))*pMiss; 
  pnew = p.*pnew;
  pnew = pnew/sum(pnew);
end

function pnew = move(p)
   pH = [0.1 0.8 0.1];
   pnew = conv(p,pH,'same');
   pnew = pnew/sum(pnew);
   pnew = [pnew(end) pnew(1:end-1)];
end