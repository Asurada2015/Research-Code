
% This basic demo contains the source codes for the MO-MFEA-II algorithm, handling upto 2 "continuous" multi-objective 
% optimization tasks concurrently.

% Default Parameter Settings and genetic operators provided/implemented herein are in accordance with the paper
% "Cognizant Multitasking in Multiobjective Multifactorial Evolution: MO-MFEA-II" 
% published in IEEE Trans. Cybernetics, 2020. 

% This implementation assumes that no uniform crossover like variable-swap is applied 
% between offspring to ensure parent-centric crossover operations with minimum chromosome 
% disruptions - thus allowing  to clearly observe the effects of intertask implicit genetic transfers.

% For any bugs or suggestions, please contact: Bali Kavitesh Kumar (Email: bali0001@e.ntu.edu.sg)

clc
clear all
    
 % load data % Known PF data of test function
load sphere
load concave
load circle

%load M % Rotattion matrix
 M= 1; 
for run = 1:3
    
    f1='p1t1';
    dim = 10;
    % Assigning upper and lower bounds of search space of task 1
    L1=-100*ones(1,dim);
    U1=100*ones(1,dim);
    L1(1)=0;U1(1)=1;
    %L1(2)=0;U1(2)=1;
    pop1=50; % Population size for task 1
    pf1 = circle;
    
    
    f2='p1t2';
    % Assigning upper and lower bounds of search space of task 2
    L2=-100*ones(1,dim);
    U2=100*ones(1,dim);
    L2(1)=0;U2(1)=1;
   % L2(2)=0;U2(2)=1;
    pop2=50; % Population size for task 2
    pf2 = concave;
    
    rmp=0; % Random mating probability - learned online for MO-MFEA-II
    gen = 100; % Maximum Number of generations
    muc = 10; % Distribution Index of SBX crossover operator
    mum = 10; % Distribution Index of Polynomial Mutation operator
    prob_vswap = 0; % Probability that certain pair of variables are swapped (uniform crossover-like) during SBX crossover. Change to prob_swap = 0.5 for enhanced global search at the cost of high chromosome disruption.
    prob_xover = 1;
    store_Instance2(run).data = MOMFEA2(L1,U1,f1,pop1,L2,U2,f2,pop2,pf1,pf2,rmp,M,gen,muc,mum,prob_vswap,prob_xover);    
end
save('store_Instance2','store_Instance2');


