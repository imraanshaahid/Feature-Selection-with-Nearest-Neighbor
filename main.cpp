#include<bits/stdc++.h>

using namespace std;

class data{

    public:
    vector< vector< long double> > v;
    int featureList;
    int totalFeatures;
};
clock_t start;

float checkFunc(data feat) {
    data subs;
    int c = 0;int i = 0;
    while(i < (feat.v)[0].size()) {
            int j = 0;int a=0;
            long double iCheck[100003];
        while(j < feat.v.size()) {
            vector<long double> tmp = feat.v[j];
            iCheck[a++]=tmp[i];
            tmp.erase(tmp.begin() + i);
            subs.v.push_back(tmp);
            j++;
        }
        data n ;
        n.v = subs.v;
        long double mDst = INT_MAX; int classf = iCheck[0];
        for(int i = 0; i < subs.v[0].size(); i++) {
            long double d = 0.0;
            for(int j = 1; j < subs.v.size(); j++) {
                d = d + ((subs.v[j][i] - iCheck[j])*(subs.v[j][i] - iCheck[j]));
            }
            if(d < mDst) { mDst = d; classf = (int)subs.v[0][i]; }
        }
        if( (int)classf == (int)iCheck[0]) {
            c++;
        }
        subs.v.clear();
    	i++;
    }
    float ans = ((float)c / (float)feat.v[0].size()) * 100;
    return ans;

}

void fwdSelect(data training_set, int ft) {

     int finalFeat[100003]={-1};
     vector<int> lbest;
    double precision, global = 0.0;
    int s=0;int i = 1;
    while(i <= ft) {
        double localmax = 0.0;
        vector<int> tmpMax;
        for(int j = 1; j <= ft; j++) {
            data tmp;
            vector<int> tmpLocal;
            tmp.v.push_back(training_set.v[0]);
            tmpLocal = lbest;

            vector<int> featureList(100000);
            for(int i=0;i<100000;i++){
                featureList[i]=i;
            }
            for(int x = 0; x < tmpLocal.size(); x++) {
                    tmp.v.push_back( training_set.v[tmpLocal[x]] );
            }
                int k, s = tmpLocal.size();
                for(k=0;k<s;k++)
                    if(tmpLocal[k]==j)
                        break;

                if(k!=s)
                    continue;

                tmp.v.push_back(training_set.v[j]);
                tmpLocal.push_back(j);
                cout << "Using the feature ";cout<<" {";
                for(int i = 0; i < tmpLocal.size(); i++) {
                    cout << tmpLocal[i] << " ";
                }
                cout<<"} ";
                data n; n = tmp;
                precision = checkFunc(n);
                cout << "accuracy: " << precision << endl;
                if(precision > localmax) {
                    localmax = precision; tmpMax = tmpLocal;
                }
        }
        lbest = tmpMax;
        cout << "The best feature set is: ";
        cout<<" {";
        for(int i = 0; i < lbest.size(); i++) {
                cout << lbest[i] << " ";
        }
        cout<<"} ";
        cout << "with an accuracy of " << localmax << "%" << endl;

        if(localmax > global) {
            s = lbest.size();
            for(int i=0;i<lbest.size();i++)
                finalFeat[i]=lbest[i];
            global = localmax;
        }
        i++;
    }
    vector<int> ftlist(100000);
    for(int i=0;i<100000;i++){
        ftlist[i]=i;
    }
    cout << endl << "Search completed." << endl;
    cout << "The final best set : ";
    int ct=0;
    for(int i=0;i<10000;i++)
        if(finalFeat[i]!=-1)
            ct++;
    i = 0;
    cout<<" {";
    while(i < s) {
        cout << finalFeat[i++] << " ";
    }
    cout<<"} ";
    cout << "with an accuracy of " << global << "%" << endl;
}

void bkdSelect(data t_set, int totalFtr) {

     int num=1;
     int finalFeat[100003]; int s=0;
    for(int i=0;i<totalFtr;i++)
        finalFeat[i]=num++;

    vector<int> lbst;
    for(int i=0;i<totalFtr;i++)
        lbst.push_back(finalFeat[i]);

    double precision, global = 0.0;

    int i = 1;
    while(i < totalFtr) {
        double localmax = 0.0;
        vector<int> tmpMax;
        for( int j = 0; j <= totalFtr; j++) {
            data tmp;
            vector<int> tmpLocal;
            tmp.v.push_back(t_set.v[0]);
            tmpLocal = lbst;

             vector<int> ftlist(100000);
            for(int i=0;i<100000;i++){
                ftlist[i]=i;
            }
            for( int x = 0; x < lbst.size(); x++) {
                tmp.v.push_back( t_set.v[lbst[x]] );
            }
            int k;
            for(k=0;k<tmpLocal.size();k++)
                if(tmpLocal[k]==j)
                    break;

            if(k==tmpLocal.size())
                continue;
                 int index = k+1;
                 tmpLocal.erase(tmpLocal.begin() + index-1);
                tmp.v.erase(tmp.v.begin() + index);
                cout << "Using the feature ";cout<<" {";
                for( int i = 0; i < tmpLocal.size(); i++) {
                    cout << tmpLocal[i] << " ";
                }
                cout<<"} ";
                data n; n = tmp;
                precision = checkFunc(n);
                cout << "accuracy: " << precision << endl;
                if(precision >= localmax) { localmax = precision; tmpMax = tmpLocal; }
        }
        lbst = tmpMax;
        cout << "The best feature set is : ";cout<<" {";
        for( int i = 0; i < lbst.size(); i++) {
            cout << lbst[i] << " ";
        }
        cout<<"} ";
        cout << " with an accuracy of " << localmax << "%" << endl;

        if(localmax > global) {
            s = lbst.size();
            for(int i=0;i<s;i++)
                finalFeat[i]=lbst[i];

            global = localmax;
        }
        i++;
    }
    cout << endl << "Search completed." << endl;
    cout << "The final best set is: ";
    i = 0;
    cout<<" {";
    while(i < s) {
        cout << finalFeat[i++] << " ";
    }
    cout<<"} ";
    cout << "with a accuracy : " << global << "%" << endl;
}

int main() {

    string fname;
    int algo;
    cout << "This is a Feature Selection Algorithm." << endl;
    cout << "Name of file: " << endl;
    cin >> fname;
    cout << "Select the algo to run." << endl;
    cout << "1) Forward Selection \n2) Backward Elimination" << endl;
    cin >> algo;

	ifstream fin;
    fin.open(fname.c_str());

	data t_set;
    string z;

    getline(fin, z);
    stringstream sstream(z);
    string feature;
    while(sstream >> feature) {
         vector <long double> feats;
        feats.push_back(stold(feature));
        t_set.v.push_back(feats);
    }

    int bestfeatures[10000];
    for(int i=0;i<10000;i++){
        bestfeatures[i]=i;
    }

    while( getline(fin, z) ) {
        stringstream sstream(z);
        for(int i = 0; i < t_set.v.size(); i++) {
            string ft;
            if( sstream >> ft)
                (t_set.v)[i].push_back(stold(ft));
        }
    }

    fin.close();
    int numFeatures = t_set.v.size() - 1;
	cout << "Total instances: " << (t_set.v)[0].size() << endl;
	cout << "Total features: " << numFeatures << endl;
	cout << "Running nearest neighbor with all the features, using \"leave one out\" evaluation, accuracy is ";
	data n;n.v = t_set.v;
	cout << checkFunc(n) << "%" << endl;

	switch(algo){
        case 1:fwdSelect(t_set, numFeatures);
                break;
        default : bkdSelect(t_set, numFeatures);
	}

    return 0;
}
