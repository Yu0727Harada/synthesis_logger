
#include <iostream> // cout, endl, cin
#include <string> // string, to_string, stoi
#include <vector> // vector
#include <algorithm> // min, max, swap, sort, reverse, lower_bound, upper_bound
#include <utility> // pair, make_pair
#include <tuple> // tuple, make_tuple
#include <cstdint> // int64_t, int*_t
#include <cstdio> // printf
#include <map> // map
#include <queue> // queue, priority_queue
#include <set> // set
#include <stack> // stack
#include <deque> // deque
#include <unordered_map> // unordered_map
#include <unordered_set> // unordered_set
#include <bitset> // bitset
#include <cctype> // isupper, islower, isdigit, toupper, tolower
#include <math.h>
#include <ios>
#include <iomanip>
#include <numeric>
#include <fstream>
#include <sstream>
#include <regex>



#define all(x) (x).begin(),(x).end()
#define rall(x) (x).rbegin(),(x).rend()
template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return 1; } return 0; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return 1; } return 0; }
typedef long long ll;
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ll> vl;
const long long LINF =1e18;
const int INF = 1e9;



int main() {
    string str_buf;
    string str_conma_buf;
    string input_csv_file_path;
    string output_csv_file_path;

    //CSVファイルの読み込み
    cout<<"読み込むCSVファイルのパスを入力してください"<<endl;
    cin>>input_csv_file_path;
    cout<<"書き込むCSVファイルのパスを入力してください"<<endl;
    cin>>output_csv_file_path;

    ifstream  ifs_csv_file(input_csv_file_path);
    ofstream ofs_csv_file(output_csv_file_path);


    vector<pair<string,int>> materials;//int 1->mL 2->uL
    vector<vector<pair<double,int>>> addition_list;


    bool q = true;
    while(getline(ifs_csv_file, str_buf)){
        istringstream  i_stream(str_buf);

        int cnt = 0;
        int sample_num;
        while(getline(i_stream,str_conma_buf,',')){
            if(q){
                if(cnt != 0){
                    string material_name = str_conma_buf;
                    material_name = regex_replace(material_name,regex("\r"),"");
                    materials.push_back({material_name,material_name[0] - '0'});
                }
            }else{
                if(cnt == 0)sample_num = stoi(str_conma_buf);
                else{
                    if(materials[cnt - 1].second == 1){
                        int add_int = stoi(str_conma_buf);
                        double add_f = stod(str_conma_buf) - add_int;

                        if(add_int != 0)addition_list[cnt - 1].push_back({add_int,sample_num});
                        if(add_f != 0.000)addition_list[cnt - 1].push_back({add_f,sample_num});
                    }else{
                        double add_f = stod(str_conma_buf);
                        if(add_f != 0.000)addition_list[cnt - 1].push_back({add_f,sample_num});
                    }

                }
            }
            cnt++;
        }
        if(q){
            addition_list.resize(materials.size());
        }
        q = false;
    }

    for (int i = 0; i < addition_list.size(); ++i) {
        sort(all(addition_list[i]));
    }



    int last_sample_num = -1;
    double last_addition_amount = -1;
    for (int i = 0; i < addition_list.size(); ++i) {
        cout<<materials[i].first<<"を添加します"<<endl;
        getchar();
        for (int j = 0; j < addition_list[i].size(); ++j) {
            if(abs(addition_list[i][j].second - last_sample_num) > 1)cout<<"飛んで"<<endl;
            if(addition_list[i][j].first != last_addition_amount)cout<<"添加量変わって"<<endl;
            cout<<addition_list[i][j].second<<":"<<addition_list[i][j].first<<endl;
            getchar();
            time_t t = time(nullptr);
            const tm* now = localtime(&t);
            ofs_csv_file<<materials[i].first<<',';
            ofs_csv_file<<addition_list[i][j].second<<',';
            ofs_csv_file<<addition_list[i][j].first<<',';
            ofs_csv_file<<now->tm_hour<<':'<<now->tm_min<<':'<<now->tm_sec<<endl;
            last_sample_num = addition_list[i][j].second;
            last_addition_amount = addition_list[i][j].first;

        }
        cout<<materials[i].first<<"の添加は終了です"<<endl;
        getchar();
    }

    cout<<"全ての添加が終了しました。恒温槽に移したらenterを押して時刻を記録します。"<<endl;
    getchar();
    time_t t = time(nullptr);
    const tm* now = localtime(&t);
    ofs_csv_file<<"実験終了時刻";
    ofs_csv_file<<now->tm_hour<<':'<<now->tm_min<<':'<<now->tm_sec<<endl;
    cout<<"時刻を記録しました。終了します。"<<endl;

    return 0;
}
