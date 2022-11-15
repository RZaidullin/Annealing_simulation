#include <iostream>
#include <cstdlib>
#include <chrono>
#include <ctime>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>

std::vector<std::vector<int>> read_from_csv ();

int test_data_counter = 0;

// template<typename TData>
class ABC_Presentation {
public:
    ABC_Presentation () {}

    virtual int count_score () = 0;

    virtual ~ABC_Presentation() {}
};

class Presentation : ABC_Presentation {
// private:
public:
    std::vector<std::vector<int>> HP;
    long long score;                        // criterion
    // double T;                            // temperature
    // int proc_num;
    // int work_num;
// public:
    Presentation () {}

    Presentation (long long proc_num, long long work_num, std::vector<int>& work_times) {
        std::srand(std::time(nullptr));
        long long random_proc;
        HP = std::vector<std::vector<int>>(proc_num);
        for (auto it = work_times.begin(); it != work_times.end(); it++){
            random_proc = std::rand() % proc_num;
            HP[random_proc].push_back(*it);
        }
        score = this->count_score();
        // T = 1000.0;
    }

    Presentation& operator=(const Presentation& other){
        this->HP = other.HP;
        this->score = other.score;
        // this->T = other->T
        return *this;
    }

    int count_score () {
        int tmp = 0, additional;
        for (const auto& s : this->HP) {
            additional = 0;
            for (const auto& it: s) {
                tmp += it + additional;
                additional += it;
            }
        }
        // std::cout<<tmp<<std::endl;
        return tmp;
    }

    void print() {
        int cnt = 1;
        std::cout << "Best score is " << this->score << std::endl;
        for (const auto& s : this->HP) {
            std::cout<<"Works on "<<cnt<< " processor: ";
            cnt++;
            for (const auto& it: s) {
                std::cout<<it<<" ";
            }
            std::cout<<std::endl;
        }
    }

    std::vector<std::vector<int>> get_HP () {
        return this->HP;
    }

    int get_score () {
        return this->score;
    }
};

class ABC_Mutation {

};

class Mutation {
private:
    // Presentation PT;
    int permutation;
    int transfer;
public:
    Mutation (int perm = 1, int trans = 1) : permutation(perm), transfer(trans) {};

    void mutate(std::vector<std::vector<int>> & HP) {
        // std::srand(std::time(nullptr));
        long long int proc_num = HP.size(), random_proc1, random_proc2, random_work1, random_work2, random_proc1_work_num, random_proc2_work_num, buf1;

        // std::cout<<proc_num<<std::endl;
        long long p;
        for (int i = 0; i < this->permutation; i++){
            // std::cout<<"Entered mutate for "<<i<< " Procs "<<proc_num<<std::endl;
            p = std::rand();
            // std::cout<<p<<std::endl;
            // std::cout<<"Random proc: "<<p % proc_num<<std::endl;
            // random_proc1 = std::rand() % proc_num;
            random_proc1 = p % proc_num;
            // random_proc1 = (long long int)((double)rand() / ((double)RAND_MAX + 1) * proc_num);
            // std::cout<<random_proc1<<std::endl;
            while(HP[random_proc1].size() < 1){
                random_proc1 = std::rand() % proc_num;
                // std::cout<<" Ridicuoulos "<<random_proc1<<std::endl;
            }
            random_proc1_work_num = HP[random_proc1].size();
            random_work1 = std::rand() % random_proc1_work_num;
            // std::cout<<"Random work1: "<<random_work1<<std::endl;
            
            random_proc2 = std::rand() % proc_num;
            // std::cout<<"Random proc2: "<<random_proc2<<std::endl;
            // while(HP[random_proc2].size() < 2)
            //     random_proc2 = std::rand() % proc_num;
            while(HP[random_proc2].size() < 1 || random_proc1 == random_proc2 && random_proc1_work_num == 1){
                random_proc2 = std::rand() % proc_num;
                // std::cout<<" Ridicuoulos "<<random_proc2<<std::endl;
            }
            // random_proc1_work_num = HP[random_proc1].size();
            random_proc2_work_num = HP[random_proc2].size();
            // random_work1 = std::rand() % random_proc1_work_num;
            // std::cout<<" !!!!!! "<<random_proc2_work_num<<std::endl;
            random_work2 = std::rand() % random_proc2_work_num;
            // std::cout<<"Random work2: "<<random_work2<<std::endl;
            // std::cout<<random_proc1<<" "<<random_work1<<" "<<random_work2<<std::endl;
            while(random_work1 == random_work2 && random_proc1 == random_proc2){
                random_work2 = std::rand() % random_proc2_work_num;
                // std::cout<<random_proc1<<" "<<random_proc2<< " "<<random_proc1_work_num<< " " <<random_proc2_work_num<< " "<<random_work2<<std::endl;
            }
            // std::cout<<random_proc1<<" "<<random_work1<<" "<<random_work2<<std::endl;
            // std::swap(HP[random_proc1][random_work1], HP[random_proc1][random_work2]);

            // std::cout<<random_proc1<<" "<<random_work1<<" "<< random_proc2<< " "<< random_work2<<" "<<std::endl;
            // std::cout<<HP[random_proc1][random_work1]<<" "<<*(HP[random_proc1].begin() + random_work1)<<" "<< random_work2 <<std::endl;

            buf1 = HP[random_proc1][random_work1];
            HP[random_proc1].erase(HP[random_proc1].begin() + random_work1);

            HP[random_proc2].insert(HP[random_proc2].begin() + random_work2, buf1);
            // if (random_proc1 == random_proc2)
            //     random_work1++;
            // HP[random_proc1].erase(HP[random_proc1].begin() + random_work1);
            // std::cout<<std::endl;
        }

        // for (int i = 0; i < this->transfer; i++){
        //     random_proc1 = std::rand() % proc_num;
        //     while(HP[random_proc1].size() < 1)
        //         random_proc1 = std::rand() % proc_num;
            
        //     random_proc_work_num = HP[random_proc1].size();
        //     random_work1 = std::rand() % random_proc_work_num;

        //     random_proc2 = std::rand() % proc_num;
        //     while(random_proc1 == random_proc2)
        //         random_proc2 = std::rand() % proc_num;
        //     // std::cout<<random_proc1<<" "<<random_proc2<<" "<<random_work1<<std::endl;
        //     HP[random_proc2].push_back(HP[random_proc1][random_work1]);
        //     HP[random_proc1].erase(HP[random_proc1].begin() + random_work1);
        // }
    }
};

class Temperature {
public:
    virtual double new_temperature (double T_0, int iteration_number) = 0;

    virtual ~Temperature() {}
};

class Boltzmann : public Temperature {
public:
    double new_temperature (double T_0, int iteration_number) {
        return T_0 / log(1 + iteration_number);
    }
    // ~Boltzmann();
};

class Cauchy : public Temperature {
public:
    double new_temperature (double T_0, int iteration_number) {
        return T_0 / (1 + iteration_number);
    }
};

class Natural_log : public Temperature {
public:
    double new_temperature (double T_0, int iteration_number) {
        return T_0 * log(1 + iteration_number) / (1 + iteration_number);
    }
};

// template<typename TData>
class Head {
private:
    double temperature;
public:
    Head (double T = 1000.0) : temperature(T) {}

    void make_new_temperature (double T) {
        this -> temperature = T;
    }

    void main_loop () {
        // std::srand(std::time(nullptr));
        // int proc_num = 3, work_num = 6;
        // std::vector<int> work_times = {2, 3, 5, 6, 4, 1};
        auto input = read_from_csv();

        // Mutation mutation1(input[1][0] / 10, input[1][0] / 10);

        Mutation mutation1(5,5);

        Boltzmann T1;
        Cauchy T2;
        Natural_log T3;

        Temperature& T = T3;

        // Presentation HP1(proc_num, work_num, work_times), res, tmp;
        Presentation HP1(input[test_data_counter][0], input[test_data_counter + 1][0], input[test_data_counter + 2]), res, tmp;
        test_data_counter += 3;
        // HP1.print();
        // std::cout<<HP1.get_score()<<std::endl;
        std::cout << "Start criterion: " << HP1.get_score() << " ";

        res = HP1;
        tmp = HP1;
        long long stop_criterion = 0, tmp_score, delta, best_score = HP1.get_score(), iteration = 0, the_best_score;
        double p;
        the_best_score = best_score;
        
        while (stop_criterion < 100) {
            iteration++;
            for (int i = 0; i < 100; ++i){
                // std::srand(std::time(nullptr));
                // std::cout<<"print1"<<std::endl;
                mutation1.mutate(tmp.HP);
                // std::cout<<"print2"<<std::endl;
                tmp.score = tmp.count_score();
                // tmp.print();
                tmp_score = tmp.score;
                // std::cout<<i<<" "<<tmp_score<<" * "<<best_score<<std::endl;
                delta = tmp_score - best_score;
                if (delta < 0) {
                    // std::cout<<" "<<delta<<std::endl;
                    res = tmp;
                    HP1 = tmp;
                    best_score = tmp_score;
                    // if (the_best_score > best_score)
                        stop_criterion = 0;
                        // the_best_score = best_score;
                    // else
                    //     the_best_score = best_score;
                }
                else {
                    auto buf = - double(delta) / this->temperature;
                    // std::cout<<buf << " "<< exp(buf) <<" ";
                    p = expl(-double(delta) / this->temperature);
                    // std::cout<<((double) rand() / (RAND_MAX))<<" "<<p<<" "<<tmp_score<<" "<<best_score<<" "<<delta<<" "<<this->temperature<<std::endl;
                    if (rand() / 32767 < p){
                        HP1 = tmp;
                        best_score = tmp_score;
                        // stop_criterion = 0;
                    }
                    else {

                        tmp = HP1;
                    }
                }
            }
            // break;
            stop_criterion++;
            // std::cout<<stop_criterion<< "  ****** "<<the_best_score<< " "<< best_score<<std::endl;
            if(stop_criterion == 100){

                break;
            }
            // this->temperature = T.new_temperature(this->temperature, iteration);
            // std::cout<<this->temperature<<std::endl;
        }

        // if(tmp_score)

        // res.print();
        // std::cout<<res.get_score()<<std::endl;
        std::cout << "Final criterion: " << res.get_score() << " ";

        // Presentation HP2(input[0][0], input[1][0], input[2]);
        // HP2.print();
        // mutation1.mutate(HP2.HP);
        // HP2.print();
    }


};

int main() {
    std::srand(std::time(nullptr));
    // std::srand(unsigned(time(NULL)));

    // int proc_num = 3, work_num = 6;
    // std::vector<int> work_times = {2, 3, 5, 6, 4, 1};
    // auto input = read_from_csv();

    // Mutation mutation1(2, 2);

    // Presentation HP1(proc_num, work_num, work_times), HP3(1, 6, work_times);
    // HP1.print();
    // mutation1.mutate(HP1.HP);
    // HP3 = HP1;
    // HP3.print();

    Head H1(10000.0); // , H2(10000.0);

    for (int i = 0; i < 80; i++) {
        // std::cout << << " ";
        auto t_start = std::chrono::high_resolution_clock::now();
        H1.main_loop();
        H1.make_new_temperature(10000.0);
        auto t_end = std::chrono::high_resolution_clock::now();
        auto t_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(t_end - t_start).count();
        std::cout << "Duration:" << t_duration / 1e9 << std::endl;
    }
    // H1.main_loop();
    // H2.main_loop();
    // H1.make_new_temperature(10000.0);
    // H1.main_loop();

    // Presentation HP2(input[0][0], input[1][0], input[2]);
    // HP2.print();
    // mutation1.mutate(HP2.HP);
    // HP2.print();
    // return 0;
}

std::vector<std::vector<int>> read_from_csv () {
    std::fstream fin;
    fin.open("example.csv", std::fstream::in);

    std::vector<std::vector<int>> content;
    std::vector<int> row;
    std::string line, word, temp;

    row.clear();
    if(fin.is_open()){
        while(std::getline(fin, line, '\n')){
            row.clear();
            std::stringstream str1(line);
            while(std::getline(str1, word, ','))
                row.push_back(std::stoi(word));
            content.push_back(row);
        }
    }
    else
        std::cout<<"Could not open the file\n";
    
    // for(int i=0; i<content.size(); i++){
    //     for(int j=0; j<content[i].size(); j++){
    //         std::cout << content[i][j]<<' ';
    //     }
    //     std::cout << "\n";
    // }
    return content;
}
