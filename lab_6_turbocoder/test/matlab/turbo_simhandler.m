clc; clear; close;
%% Simulation data
s = RandStream('mt19937ar','Seed',1);
RandStream.setGlobalStream(s);
L = 16; %Interleaver length

num_invals = 16;

var_input = 3;
switch var_input
    case 1
        coder_in_data = randi([0 1], 1, num_invals);
    case 2
        coder_in_data = zeros(1,num_invals);
        coder_in_data(5) = 1;
        coder_in_data(3) = 1;
    case 3
        coder_in_data = zeros(1,num_invals);
        coder_in_data(1:2:num_invals) = 1;
    case 4
        coder_in_data = ones(1,num_invals);
end

T = num_invals+L;
coder_in_data = boolean(coder_in_data);
coder_in_ts = timeseries(coder_in_data);

simOut = sim('Turbo');
% simOut = sim('RSC_1_2');

save coder_out;
% load coder_out;
coder_out_data = coder_out.data;
coder_out_data = coder_out_data';
coder_out_data = coder_out_data(:);
coder_out_data = coder_out_data(3*L+1:end);

%% Export to file
dlmwrite('turbo_input.dat',coder_in_data);
dlmwrite('turbo_output.dat',coder_out_data);