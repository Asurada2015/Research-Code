function saveCompare(algoNameList, benchNameList, reps, taskNum, gen)
    algoNum = length(algoNameList);
    benchNum = length(benchNameList);

    % 构造访问每个任务的下标矩阵
    Task = zeros(taskNum, reps);

    k = 1;

    for i = 1:reps

        for task_i = 1:taskNum
            Task(task_i, i) = k;
            k = k + 1;
        end

    end

    % load and prepare
    benchTaskAlgoEBF = zeros(benchNum, taskNum, algoNum * reps, gen);
    clockData = zeros(benchNum, algoNum);

    for algo_i = 1:algoNum
        dataName = ['data_', algoNameList{algo_i}];
        load(['./Data/', dataName], dataName);
        data = eval(dataName);

        for bench_i = 1:benchNum
            benchData = data(bench_i);
            clockData(bench_i, algo_i) = benchData.wall_clock_time;

            for task_i = 1:taskNum
                benchTaskAlgoEBF(bench_i, task_i, (algo_i - 1) * reps + 1:algo_i * reps, :) = benchData.EvBestFitness(Task(task_i, :), 1:gen); % reps * gen
            end

        end

    end

    % calculate score
    score = zeros(benchNum, algoNum, gen);
    scoreEnd = zeros(benchNum, algoNum);
    convergence = zeros(benchNum, task_i, algoNum, gen);

    for bench_i = 1:benchNum

        for task_i = 1:taskNum
            meanEBF = mean(benchTaskAlgoEBF(bench_i, task_i, :, :));
            stdEBF = std(benchTaskAlgoEBF(bench_i, task_i, :, :));
            perScore = (benchTaskAlgoEBF(bench_i, task_i, :, :) - meanEBF) ./ stdEBF;

            perAlgoScore = zeros(1, taskNum, algoNum, gen);

            for algo_i = 1:algoNum
                perAlgoScore(1, task_i, algo_i, :) = mean(perScore(1, 1, (algo_i - 1) * reps + 1:algo_i * reps, :));
                convergence(bench_i, task_i, algo_i, :) = mean(benchTaskAlgoEBF(bench_i, task_i, (algo_i - 1) * reps + 1:algo_i * reps, :));
            end

        end

        score(bench_i, :, :) = reshape(mean(perAlgoScore), [1, algoNum, gen]);
        scoreEnd(bench_i, :) = reshape(score(bench_i, :, gen), [1, algoNum]);

    end

    % save data
    mkdir('./Results_Compare/')
    scoreFile = fopen('./Results_Compare/score.txt', 'wt');
    clockFile = fopen('./Results_Compare/clock.txt', 'wt');

    % save score
    for bench_i = 1:length(benchNameList)

        for algo_i = 1:length(algoNameList)
            % 每个算法数据
            fprintf(scoreFile, '%f\t', scoreEnd(bench_i, algo_i));
            fprintf(clockFile, '%f\t', clockData(bench_i, algo_i));
        end

        fprintf(scoreFile, '\n');
        fprintf(clockFile, '\n');

    end

    % draw convergence figure
    mkdir('./Results_Figure/')

    for bench_i = 1:benchNum

        for task_i = 1:taskNum
            fig = figure('Visible', 'off');
            x = 1:gen;

            for algo_i = 1:length(algoNameList)
                y = log(reshape(convergence(bench_i, task_i, algo_i, :), [1, gen]));
                plot(x, y, ...
                    'LineWidth', 1.5)
                hold on
            end

            % plot(reshape(score(bench_i, :, :), [algoNum, gen]))
            title(benchNameList{bench_i})
            xlabel('Generation')
            ylabel('log(Score)')
            legend(strrep(algoNameList, '_', '\_'))

            saveas(fig, ['./Results_Figure/', int2str(bench_i), '_', benchNameList{bench_i}, int2str(task_i), '.png']);
        end

    end

end
