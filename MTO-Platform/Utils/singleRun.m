function data = singleRun(algo_obj, prob_obj)
    data = algo_obj.run(prob_obj.getTasks());
end
