#include "ResultJudge.h"

bool compare_acc_predict(const ResultNode& n1, const ResultNode& n2){
	return n1.val_predict>n2.val_predict;
}

bool compare_acc_true(const ResultNode& n1, const ResultNode& n2){
	return n1.val_true>n2.val_true;
} 

double ResultJudge::dcg(int n){
	__list_node.sort(compare_acc_predict);
	size_t i=1;
	double result=0;
	double fac = log(2.);
	for(Results::const_iterator ni=__list_node.begin(); ni!=__list_node.end(); ++ni){
		result+=(pow(2.0,ni->val_true)-1)*fac/log(1.+i);
		++i;
		if(i>n)
			break;
	}
	return result;
}

double ResultJudge::mdcg(int n){
	__list_node.sort(compare_acc_true);
	size_t i=1;
	double result=0;
	double fac = log(2.);
	for(Results::const_iterator ni=__list_node.begin(); ni!=__list_node.end(); ++ni){
		result+=(pow(2.0,ni->val_true)-1)*fac/log(1.+i);
		++i;
		if(i>n)
			break;
	}
	std::cout<<result<<std::endl;
	return result;
}

double ResultJudge::computeRMSE(){
	// rmse = sqrt(E(theta-theta_*))
	double result=0;
	double ymin = 1e8;
	double ymax = -1e8;
	for(Results::const_iterator iter=__list_node.begin(); iter!=__list_node.end(); ++iter){
		result+=(iter->val_true-iter->val_predict)*(iter->val_true-iter->val_predict);
		if(ymin>iter->val_true)
			ymin = iter->val_true;
		if(ymax<iter->val_true)
			ymax = iter->val_true;
	}
	return sqrt(result/__list_node.size())/(ymax-ymin);
}

double ResultJudge::computeNDCG(int n){
	if(n==-1){
		n = __list_node.size();
	}
	return dcg(n)/mdcg(n);
}

double ResultJudge::computeMAP(int n){
	return 0.;
}