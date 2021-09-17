function Tasks = CI_L
    load('CI_L.mat') % loading data from folder ./Tasks
    dim = 50;
    Tasks(1).dims = dim;
    Tasks(1).fnc = @(x)Ackley(x, Rotation_Task1, GO_Task1);
    Tasks(1).Lb = -50 * ones(1, dim);
    Tasks(1).Ub = 50 * ones(1, dim);

    Tasks(2).dims = dim;
    Tasks(2).fnc = @(x)Schwefel(x);
    Tasks(2).Lb = -500 * ones(1, dim);
    Tasks(2).Ub = 500 * ones(1, dim);
end
