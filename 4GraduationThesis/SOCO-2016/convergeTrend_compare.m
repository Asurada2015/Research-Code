function convergeTrend_compare(data_GBO, data_GA, data_DE, data_PSO, reps, gen, benchNum, taskNum)
    benchName = {'CI-HS', 'CI-MS', 'CI-LS', 'PI-HS', 'PI-MS', 'PI-LS', 'NI-HS', 'NI-MS', 'NI-LS'};

    Task = zeros(taskNum, reps);

    k = 1;

    for i = 1:reps

        for task_i = 1:taskNum
            Task(task_i, i) = k;
            k = k + 1;
        end

    end

    x = zeros(1, gen);

    for i = 1:gen
        x(i) = i;
    end

    mkdir('./Results_compare/')
    bestSolutionGBO = fopen('./Results_compare/bestSolutionGBO.txt', 'wt');
    bestSolutionGA = fopen('./Results_compare/bestSolutionGA.txt', 'wt');
    bestSolutionDE = fopen('./Results_compare/bestSolutionDE.txt', 'wt');
    bestSolutionPSO = fopen('./Results_compare/bestSolutionPSO.txt', 'wt');
    aveSolutionGBO = fopen('./Results_compare/aveSolutionGBO.txt', 'wt');
    aveSolutionGA = fopen('./Results_compare/aveSolutionGA.txt', 'wt');
    aveSolutionDE = fopen('./Results_compare/aveSolutionDE.txt', 'wt');
    aveSolutionPSO = fopen('./Results_compare/aveSolutionPSO.txt', 'wt');
    stdGBO = fopen('./Results_compare/stdGBO.txt', 'wt');
    stdGA = fopen('./Results_compare/stdGA.txt', 'wt');
    stdDE = fopen('./Results_compare/stdDE.txt', 'wt');
    stdPSO = fopen('./Results_compare/stdPSO.txt', 'wt');
    % clock
    clockGBO = fopen('./Results_compare/clockGBO.txt', 'wt');
    clockGA = fopen('./Results_compare/clockGA.txt', 'wt');
    clockDE = fopen('./Results_compare/clockDE.txt', 'wt');
    clockPSO = fopen('./Results_compare/clockPSO.txt', 'wt');

    for i = 1:benchNum
        aveInd = gen;

        GBO = data_GBO(i);
        GA = data_GA(i);
        DE = data_DE(i);
        PSO = data_PSO(i);

        GBO_end = GBO.EvBestFitness(:, aveInd);
        GA_end = GA.EvBestFitness(:, aveInd);
        DE_end = DE.EvBestFitness(:, aveInd);
        PSO_end = PSO.EvBestFitness(:, aveInd);

        for task_i = 1:taskNum
            objTaskGBO(task_i, :) = mean(GBO.EvBestFitness(Task(task_i, :), :));
            bestTaskGBO(task_i, :) = min(min(GA.EvBestFitness(Task(task_i, :), :)));
            aveTaskGBO(task_i, :) = objTaskGBO(task_i, aveInd);
            stdTaskGBO(task_i, :) = std(GBO_end(Task(task_i, :)));

            objTaskGA(task_i, :) = mean(GA.EvBestFitness(Task(task_i, :), :));
            bestTaskGA(task_i, :) = min(min(GA.EvBestFitness(Task(task_i, :), :)));
            aveTaskGA(task_i, :) = objTaskGA(task_i, aveInd);
            stdTaskGA(task_i, :) = std(GA_end(Task(task_i, :)));

            objTaskDE(task_i, :) = mean(DE.EvBestFitness(Task(task_i, :), :));
            bestTaskDE(task_i, :) = min(min(DE.EvBestFitness(Task(task_i, :), :)));
            aveTaskDE(task_i, :) = objTaskDE(task_i, aveInd);
            stdTaskDE(task_i, :) = std(DE_end(Task(task_i, :)));

            objTaskPSO(task_i, :) = mean(PSO.EvBestFitness(Task(task_i, :), :));
            bestTaskPSO(task_i, :) = min(min(PSO.EvBestFitness(Task(task_i, :), :)));
            aveTaskPSO(task_i, :) = objTaskPSO(task_i, aveInd);
            stdTaskPSO(task_i, :) = std(PSO_end(Task(task_i, :)));
        end

        % clock
        aveClockGBO = GBO.wall_clock_time;
        aveClockGA = GA.wall_clock_time;
        aveClockDE = DE.wall_clock_time;
        aveClockPSO = PSO.wall_clock_time;
        fprintf(clockGBO, '%f\n', aveClockGBO);
        fprintf(clockGA, '%f\n', aveClockGA);
        fprintf(clockDE, '%f\n', aveClockDE);
        fprintf(clockPSO, '%f\n', aveClockPSO);

        for task_i = 1:taskNum
            fprintf(bestSolutionGBO, '%f\n', bestTaskGBO(task_i, :));
            fprintf(aveSolutionGBO, '%f\n', aveTaskGBO(task_i, :));
            fprintf(stdGBO, '%f\n', stdTaskGBO(task_i, :));

            fprintf(bestSolutionGA, '%f\n', bestTaskGA(task_i, :));
            fprintf(aveSolutionGA, '%f\n', aveTaskGA(task_i, :));
            fprintf(stdGA, '%f\n', stdTaskGA(task_i, :));

            fprintf(bestSolutionDE, '%f\n', bestTaskDE(task_i, :));
            fprintf(aveSolutionDE, '%f\n', aveTaskDE(task_i, :));
            fprintf(stdDE, '%f\n', stdTaskDE(task_i, :));

            fprintf(bestSolutionPSO, '%f\n', bestTaskPSO(task_i, :));
            fprintf(aveSolutionPSO, '%f\n', aveTaskPSO(task_i, :));
            fprintf(stdPSO, '%f\n', stdTaskPSO(task_i, :));
        end

        for task_i = 1:taskNum
            h = figure('visible', 'off');
            plot(x, objTaskGBO(task_i, 1:gen), 'r', 'Linewidth', 1);
            hold on;
            plot(x, objTaskGA(task_i, 1:gen), 'y', 'Linewidth', 1);
            hold on;
            plot(x, objTaskDE(task_i, 1:gen), 'g', 'Linewidth', 1);
            hold on;
            plot(x, objTaskPSO(task_i, 1:gen), 'b', 'Linewidth', 1);
            hold on;

            title(['T', num2str(task_i), ' ', 'in', ' ', char(benchName(i))]);
            t = legend('GBO', 'GA', 'DE', 'PSO');
            xlabel('Generation');
            ylabel('Cost');
            set(t, 'Fontsize', 20);
            set(gca, 'Fontsize', 16);

            outPath = ['./Results_compare/', char(benchName(i)), 'Task', num2str(task_i), '.png'];
            print(h, '-dpng', outPath);
            close(h);

        end

    end

end
