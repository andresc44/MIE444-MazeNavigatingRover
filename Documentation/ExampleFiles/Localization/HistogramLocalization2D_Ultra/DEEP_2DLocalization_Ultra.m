%provide measurements and movements
heading = 270; %270 degrees implied down
m_u = [ 3,  3,  3,  1,  1,  1,  1,  5,  5,  5,  5,  0,  0,  0,  0,  5,  5,  5,  5,  2,  2,  2,  2,  2,  2];
m_m = ['w','w','w','d','a','d','w','w','w','w','w','w','w','w','w','w','w','w','w','w','d','w','w','w','a'];

%initalization of the world
dim1 = 32; dim2 = 16; 
locationindex = reshape(1:dim1*dim2,dim1,dim2)'; 
n = numel(locationindex);
rand('twister',5489);
bw = reshape(randi([0 1],n,1),dim2,dim1); %0 = black, 1 = white

%make blocks
M = zeros(size(bw));
Blocks = [2, 3; 3, 2; 4, 3; 5, 1; 5, 3; 7, 1; 7, 3; 7, 4;];
for xx = 1:size(Blocks,1),
	x = Blocks(xx,1); y = Blocks(xx,2);
	M(1+(y-1)*4:(y-1)*4+4, 1+(x-1)*4:(x-1)*4+4) = 1;
end
M = [ones(dim2,1) M ones(dim2,1)];
M = [ones(1, dim1+2); M; ones(1, dim1+2)];

%generate ultrasonic world
ultra = zeros(size(bw));
for sec_row = 1:4:dim2,
    for sec_col = 1:4:dim1,
        segRow = M(sec_row+2, sec_col:sec_col+5);
        segCol = M(sec_row:sec_row+5, sec_col+2);
        val = sum(segRow)+sum(segCol);
        if val == 2 && sum(segRow)~=1,
            val = 5;
        end
        ultra(sec_row:sec_row+3, sec_col:sec_col+3) = val;
    end
end

%create mask for blocks
M = abs(M-1);
M = M(2:end-1, 2:end-1);
figure; imagesc((bw+1).*M); colormap(gray);

%initialize probability
p = ones(dim2,dim1)*(1/n); 

figure;
%localizatoin loop

for k = 1:length(m_m),

    %sensor update
    p = sense_u(ultra, M, p, m_u(k));

    imagesc(p);
    title(['step: ' num2str(k)]);
    pause;

    %movement update
    [p, heading] = move(p, M, heading, m_m(k));

end
