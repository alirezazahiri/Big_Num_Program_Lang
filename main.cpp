#include <bits/stdc++.h>
#include <conio.h>
#include <string>

using namespace std; 

string sum_neg_or_pos(string s1, string s2);
string sub_neg_or_pos(string s1, string s2);
string div_neg_or_pos(string s1, string s2);
string mul_neg_or_pos(string s1, string s2);
string pow_neg_or_pos(string s1, string s2);

void diagnose_command(string command);

void load_data();

struct Numbers{
	string name;
	string data;
};

struct Numbers num1 ;
struct Numbers num2 ; 

struct vector <Numbers> numbers ;  
vector <string> file_code ; 

Numbers get_numbers(Numbers num, string input);

int number_of_lines(string file_name){
	ifstream file ; 
	file.open(file_name, ios::in);
	
	int i = 0 ; 
	string line;
	while (getline(file, line)) {
	    i++ ; 
	}
	return i ; 
}

void write_data(Numbers num){
	
	ofstream file;
	
	file.open("history.txt", ios::app);
	file << num.name << '\t' << num.data << '\n'; 
	numbers.push_back(num);

	file.close() ; 
}

void load_data(){
	ifstream file;
	
	file.open("history.txt"); 
	
	numbers.clear();
	
	if(!file){
		cout << "CAN'T FIND FILE :(";
		exit(0);
	}
	Numbers num ; 
	
	while(!file.eof()){
		if(numbers.size() == number_of_lines("history.txt")){
			break; 
		}
		file >> num.name >> num.data ; 
		numbers.push_back(num) ; 
	}
	
	file.close(); 
}

void update_file(){
	
	ofstream file;
	file.open("history.txt");
	
	file.clear();
	
	for(Numbers in: numbers){
		file << in.name << '\t' << in.data << '\n' ; 
	}
	file.close();
}

string remove_last_char(string str){
	
	string new_str = "";
	
	for (int i = 0 ; i < str.length()-1 ; i++){
		new_str += str[i];
	}
	
	return new_str ; 
}

string remove_first_char(string str){
	
	string new_str = "";
	
	for (int i = 1 ; i < str.length() ; i++){
		new_str += str[i];
	}
	
	return new_str ; 
}

Numbers find_el(string num){
	bool found = false ; 
	
	Numbers var ; 
	var.name = "";
	var.data = "";
	
	for(Numbers in: numbers){
		if(in.name == num){
			var = in ; 
			return var; 
		}
	}
	
	var.name = "new"; 
	var.data = num ; 
	
	return var;
}

string calculate_value(Numbers n1, Numbers n2, char choice){
	if (n1.data == "" || n2.data == ""){
		cout << "ELEMENT NOT FOUND!";
		return "";
	}
	else{
		switch(choice){
		case '+': 
		return sum_neg_or_pos(n1.data, n2.data); 
		
		case '-': 
		return sub_neg_or_pos(n1.data, n2.data); 
		
		case '*': 
		return mul_neg_or_pos(n1.data, n2.data); 
		
		case '/': 
		return div_neg_or_pos(n1.data, n2.data); 
		
		case '^': 
		return pow_neg_or_pos(n1.data, n2.data); 
		}
	}
}

string convert_to_num(string str){
	
	string num1= "", num2= ""; 
	char function; 
	int count = 0 ; 
	
	for(int i = 0; i < str.length(); i++){
		
		if(str[i] == '+' || str[i] == '-' || str[i] == '/' || str[i] == '*' ||str[i] == '^'){
			function = str[i] ; 
			break;
		}
		num1 += str[i] ; 
		count++;
	}
	
	for (int i = count+1 ; i < str.length(); i++){
		num2 += str[i] ; 
	}
	
	Numbers s1 = find_el(num1);
	Numbers s2 = find_el(num2);
	
	return calculate_value(s1, s2, function);
}

bool isNumber(string s){
    for (int i = 0; i < s.length(); i++)
    {
    	if (s[0] == '-'){
    		continue;
		}
    	if (!isdigit(s[i]))
            return false;
	}
    return true;
}

Numbers get_numbers(Numbers num, string input){
	
	string name;
	string equal;
	string data;
	
	int i=0;
	
	while(input[i]!=' '&&i<input.size()){
		name+=input[i];
		i++;
	}
	
	bool sp1=false;
	bool sp2=false;
	
	while(input[i]==' ' || input[i] == '\t'){
		sp1=true;
		i++;
	}
	while((input[i]!=' ' && input[i] != '\t')&&i<input.size()){
		equal+=input[i];
		i++;
	}
	while(input[i]==' ' || input[i] == '\t'){
		sp2=true;
		i++;
	}
	while((input[i]!=' ' && input[i] != '\t')&&i<input.size()){
		data+=input[i];
		i++;
	}
	
	bool error=false;
	
	if(!sp1 || !sp2)
		error=true;
		
	for(int i=0;i<name.size();i++){
		if(name[i]=='=')
			error=true;
		if(name[i]==';')
			error=true;	
	}
	if(input.size()==name.size())
		error=true;
	if(equal!="="){
		error=true;
	}
	
	if(data[data.size()-1]!=';')
		error=true;
	
	if(error)
		return num;
	
	else{
		data = remove_last_char(data);	
		if(!isNumber(data)){
			data = convert_to_num(data);
		}
		num.name = name ;
		num.data = data ; 
		
		bool flag = true ; 
		
		for (int i = 0 ; i < numbers.size() ;i++){
			if (numbers[i].name == num.name){
					numbers[i] = num;
					flag = false; 
					update_file();
					return num ;  
			}
		}
		
		if (flag){
			num.data = data ; 
		}
		
		if (num.data != ""){
			write_data(num);
		}
		
		return num ; 
	}
}

bool is_smaller(string s1, string s2){
	
	if(s1.length() < s2.length())
        return true;
        
    if(s2.length() < s1.length())
        return false;
        
    for(int i = 0 ; i < s1.length() ; i++){
    	
        if(s1[i] > s2[i])
            return false;
            
        else if(s2[i] > s1[i])
            return true;
    }
    
    return false;
}

string shift(string s){
	
    int carry = 0;
    string res = "";
    
    for(int i=0;i<s.length();i++){
        int t=(s[i] - '0') + carry;
        carry=(t%2)*10;
        res+=(char)((t/2) + '0');
    }
    while(res[0] == '0' && res.length() > 1) {
        res = res.substr(1);
    }
    return res;
}

string binary_shift(string s){
	
	int carry = 0;
	
    string res = "" ;
    
    for(int i = 0 ; i < s.length() ; i++){
        int t = (s[i] - '0') + carry;
        carry = (t % 2) * 10 ;
        res += (char)((t / 2) + '0');
    }
    
    while(res[0] == '0' && res.length() > 1) {
        res = res.substr(1);
    }
    
    return res;
}

void swap(string& s1, string& s2){
	string temp = s1;
	s1 = s2 ; 
	s2 = temp ; 
}

string reverse_str(string str){
	
	string rev = "" ; 
	for (int i = str.length() - 1 ; i >= 0  ; i--){
		rev += str[i] ; 
	}
	
	return rev;
}

// MAIN FUNCTIONS 
string sum(string s1, string s2) {
	
    if (s1.length() > s2.length()) 
    {
    	swap(s1, s2); 
	}
	
    s1 = reverse_str(s1) ; 
    s2 = reverse_str(s2) ; 
    
	string str = ""; 
    int carry = 0; 
    
    for (int i=0; i<s1.length(); i++) 
    { 
        int sum = ((s1[i] - '0')+(s2[i] - '0')+carry); 
        str += (char)(sum%10 + '0'); 
  
        carry = sum/10; 
    } 
  
    for (int i=s1.length(); i<s2.length(); i++) 
    { 
        int sum = ((s2[i] - '0') + carry); 
        str += (char)(sum%10 + '0'); 
        carry = sum/10; 
    } 
  
    if (carry > 0) 
    {
    	str += (char)(carry + '0'); 
	}
  
    str = reverse_str(str) ; 
    
    return str; 
}

string find_diff(string s1, string s2){
	string ans="";
    if(is_smaller(s1,s2)){
        swap(s1, s2);
    }

    s1 = reverse_str(s1);
    s2 = reverse_str(s2);

    int carry=0;

    for(int i=0;i<s2.length();i++){
        int sum=((s1[i]-'0') - (s2[i]-'0')-carry);

        if(sum<0){
            sum+=10;
            carry=1;
        }else
            carry=0;
        ans+=(char)(sum+'0');

    }

    for(int i=s2.length();i<s1.length();i++){
        int sum=((int)(s1[i]-'0')-carry);
        if(sum<0) {
            sum += 10;
            carry = 1;
        }else
            carry=0;
        ans+=(char)(sum+'0');
    }

     while (ans[ans.length()-1]=='0'&&ans.length()>1)
        ans=ans.substr(0, ans.length() - 1);
    
    ans = reverse_str(ans) ; 
    int counter = 0 ; 
    for(int i = 0; i < ans.length(); i++){
    	if(ans[i] != '0')
    		break;
    		
    	if (ans[0] == '0'){
    		counter++; 
		}
		else if(ans[i] == '0'){
			counter++;
		}
	}
	
	string new_str = "";
	
	for (int i = counter ; i < ans.length() ; i++){
		new_str += ans[i] ; 
	}
    
    return  ans; 
}

string sub(string s1, string s2){
	
	if(is_smaller(s1, s2)){
        return "-" + find_diff(s1, s2);
    }
    
    return find_diff(s1, s2);
}

string multiply(string s1, string s2) { 
	string res = "0";
    while (!(s1 == "0") && !(s1 == "00")) {

        if ((s1[s1.length() - 1] - '0') % 2 == 1) {
            res = sum(res, s2);
        }
        s2 = sum(s2, s2);
        s1 = shift(s1);
    }
    while (res[0] == '0' && res.length() > 1)
        res = res.substr(1);
    
    return res;
    
} 

string divide(string s1, string s2){
	
	if(is_smaller(s1,s2))
        return "0";
    int length1 = s1.length() - s2.length();
    int length2 = s1.length() - s2.length() + 1;
    
    string lowerBound = "1";
    
    for (int i = 0; i < length1 - 1; i++) {
        lowerBound += "0";
    }
    
    string upperBound = "";
    
    for (int i = 0; i < length2; i++) {
        upperBound += "9";
    }

    string ans = "";
    
    while (is_smaller("1", sub(upperBound, lowerBound))) {
        ans = shift(sum(lowerBound, upperBound));

        if (is_smaller(multiply(ans, s2), s1) || multiply(ans, s2) == s1) {
            lowerBound = ans;
        } else {
            upperBound = ans;
        }
    }
    return lowerBound;
}

string pow(string s1,string s2){
    string res="1";
    while (!(s2 == "0")){

        if((s2[s2.length()-1] - '0') % 2 == 1){
            res = multiply(res, s1);
        }
        s1 = multiply(s1, s1);
        s2 = binary_shift(s2);
    }
    return res;
}

// DETERMINE IF NUMBERS ARE NEGATIVE OR POSITIVE
string sum_neg_or_pos(string s1, string s2){ 
	if (s1[0] == '-' && s2[0] == '-'){
		s1 = remove_first_char(s1);
		s2 = remove_first_char(s2);
		
		return '-' + sum(s1, s2);
	}
	else if(s1[0] == '-'){
		s1 = remove_first_char(s1);
		
		return sub(s2, s1);
	}
	else if(s2[0] == '-'){
		s2 = remove_first_char(s2);
		return sub(s1, s2);
	}
	return sum(s1, s2) ; 
}

string sub_neg_or_pos(string s1, string s2){
	
	if (s1[0] == '-' && s2[0] == '-'){
		s2 = remove_first_char(s2);
		s1 = remove_first_char(s1);
		return sub(s2, s1);
	}
	else if(s1[0] == '-'){
		s1 = remove_first_char(s1);
		return "-" + sum(s1, s2);
	}
	else if(s2[0] == '-'){
		s2 = remove_first_char(s2);
		return sum(s1, s2);
	}
	return sub(s1, s2);
}

string mul_neg_or_pos(string s1, string s2){
	
	if (s1[0] == '-' && s2[0] == '-'){
		s1 = remove_first_char(s1);
		s2 = remove_first_char(s2);
		
		return multiply(s1, s2);
	}
	else if(s1[0] == '-'){
		s1 = remove_first_char(s1);
		
		if (s2 == "0"){
			return "0";
		}
		
		return '-' + multiply(s1, s2);
	}
	else if(s2[0] == '-'){
		s2 = remove_first_char(s2);
		
		if (s1 == "0"){
			return "0"; 
		}
		
		return '-' + multiply(s1, s2);
	}
	return multiply(s1, s2); 
}

string div_neg_or_pos(string s1, string s2){
	
	if (s1[0] == '-' && s2[0] == '-'){
		s1 = remove_first_char(s1);
		s2 = remove_first_char(s2);
		
		return divide(s1, s2);
	}
	else if(s1[0] == '-'){
		s1 = remove_first_char(s1);
		
		return '-' + divide(s1, s2);
	}
	else if(s2[0] == '-'){
		s2 = remove_first_char(s2);
		
		return '-' + divide(s1, s2);
	}
	if (s2 == "0"){
		return "inf";
	}
	
	return divide(s1, s2); 
}

string pow_neg_or_pos(string s1, string s2){
	
	if (s1[0] == '-' && s2[0] == '-'){
		s1 = remove_first_char(s1);
		s2 = remove_first_char(s2);
		
		return "0";
	}
	else if(s1[0] == '-'){
		s1 = remove_first_char(s1);
		if ((s2[s2.length()-1] - '0') % 2 == 0){
			return pow(s1, s2);
		}
		return '-' + pow(s1, s2) ; 
	}
	else if(s2[0] == '-'){
		s2 = remove_first_char(s2);
		
		if (s2[0] == '1' && s2.length() == 1 && s1 == "1")
			return "1";
		return "0";
	}
	return pow(s1, s2);
}

bool check_is_null(Numbers num){
	if ((num.data == "") || (num.name == "")){
		return true ; 
	}
	return false ; 
}

bool has_equals(string command){
	
	for(char in: command){
		if (in == '='){
			return true; 
		}
	}
	return false ; 
}

void show(string name){
	bool found = false ; 
	for(Numbers in: numbers){
		if(in.name == name){
			cout << "	  " << in.name << " = " << in.data << endl ; 
			found = true ; 
			break ; 
		}
	}
	if (!found){
		cout << "SUCH ELEMENT DOES NOT EXIST!\n" ; 
	}
}


bool is_in_file(string arg){
	
	for(Numbers in: numbers){
		if(in.name == arg){
			return true; 
		}
	}
	return false ; 
}


bool iszero(string arg1, string arg2){
	
	bool flag1 = is_in_file(arg1);
	bool flag2 = is_in_file(arg2);
	bool flag = flag1 && flag2 ; 
	
	if(flag){
		if (find_el(arg1).data == "0"){
			return true ; 
		}
	}
	else{
		cout << "NOT IN FILE!\n" ;
		return false;
	}
	
}

void replace_with_0(string arg){
	for(int i=0; i< numbers.size(); i++){
		if(numbers[i].name == arg){
			numbers[i].data = "0";
			update_file();
		}
	}
}

void replace_with_1(string arg){
	for(int i=0; i< numbers.size(); i++){
		if(numbers[i].name == arg){
			numbers[i].data = "1";
			update_file();
		}
	}
}

void replace_value(string arg, string data){
	
	for(int i = 0 ; i < numbers.size(); i++){
		if(numbers[i].name == arg){
			numbers[i].data = data ; 
			update_file();
			break ; 
		}
	}
}

void run_code(string arg, string code){
	
	int start; 
	for(int i = 0 ; i < code.length(); i++){
		if(code[i] == '='){
			start = i+1; 
			break ;
		}
	}
	
	for(int i = start; i < code.length(); i++){
		if(code[i] != ' ' || code[i] != '\t'){
			start = i + 1; 
			break; 
		}
	}
	
	string name = ""; 
	
	for(int i = start ; i < code.length(); i++){
		if(code[i] == '-' || code[i] == '+'){
			start = i;
			break ;
		}
		if(!isdigit(code[i]) && (code[i] != '-' || code[i] != '+')){
			name += code[i] ; 
		}
	}
	
	char function ;
	
	function = code[start]; 
	start++; 
	
	string s_o_d = ""; 
	
	for(int i = start; i < code.length(); i++){
		if(code[i] == ';'){
			break;
		}
		s_o_d += code[i] ; 
	}
	
	if(isNumber(s_o_d)){
		Numbers num;
		num.data = s_o_d ; 
		num.name = "var";
		string data ; 
		data = calculate_value(find_el(arg), num, function);
		replace_value(find_el(arg).name, data);
	}else{
		string data;
		data = calculate_value(find_el(arg), find_el(s_o_d), function);
		replace_value(find_el(arg).name, data);
	}
}

void goto_func(string arg1 , string arg2){
	
	int index = 1 ; 
	int line_idx = stoi(arg2);
	
	vector<string> code_backup ; 
	
	for(string code: file_code){
		code_backup.push_back(code);
	}
	
	line_idx -= 1 ;
	
	string code_to_run = file_code[line_idx] ; 
	
	string arg = ""; 
	
	for(int i = 0 ; i < code_to_run.length(); i++){
		
		if(code_to_run[i] == ' ' || code_to_run[i] == '\t' || code_to_run[i] == '=')
		{
			break;
		}
		
		arg += code_to_run[i];
	} 
	
	while(find_el(arg).data > "0"){
		cout << find_el(arg).name << " = " << find_el(arg).data << endl ;
		
		run_code(arg, code_to_run); 
		
		if(find_el(arg).data[0] == '-'){
			replace_value(find_el(arg).name, "0");
			break;
		}
	}
	
}

void diagnose_command(string command){
	
	string list_of_commands[4] = {"show", "iszero", "goto", "clearhis"} ; 
	bool flag = false ; 
	
	int count = 0; 
	
	for (int i = 0 ; i < command.length() ;i++){
		if (command[i] == '('){
			break;
		}
		count++; 
	}
	
	string cmnd_name = "" ; 
	for (int i = 0 ; i < count ; i++){
		cmnd_name += command[i] ; 
	}
	
	for(string in: list_of_commands){
		if (cmnd_name == in){
			flag = true;
		}
	}
	
	if (flag){
		string args  = ""; 
		for(int i = count+1 ; i < command.length() - 2 ;i++){
			args += command[i] ; 
		}
		
		vector <string> params; 
		string param = "" ;
		
		for (int i = 0 ; i < args.length(); i++){
			if(args[i] == ' ' || args[i] == '\t' || args[i] == ','){
				if (param != "")
					params.push_back(param); 
				param = ""; 
				continue;
			}
			param += args[i];
		}
		if (param != "")
			params.push_back(param);
		
		if(cmnd_name == "show") 
		{
			if (params.size() == 1){
				string num = params[0] ; 
				show(num);
			}
			else{
				cout << "ERROR ASSIGNING VALUE!\n" ; 
			}
		} 
		if(cmnd_name == "iszero") 
		{
			if (params.size() == 2){
				string arg1 = params[0] ;
				string arg2 = params[1] ;  
				bool flag = iszero(arg1, arg2);
				if(flag){
					replace_with_0(arg2); 
				}
				if(!flag){
					replace_with_1(arg2); 
				}
			}
			else{
				cout << "ERROR ASSIGNING VALUE!\n" ; 
			}
		}
		if(cmnd_name == "goto"){
			if(params.size() == 2){
				string arg1 = params[0] ; 
				string arg2 = params[1] ; 
				
				if (is_in_file(arg1)){
					if(find_el(arg1).data == "0"){
						cout << "ELEMENT IS ALREADY ZERO\n" ; 
					}else{
						if (isNumber(arg2)){
							goto_func(arg1, arg2);
						}
						else{
							cout << "ERROR ASSIGNING VALUE!\n"; 
						}
					}
				}
			}	
		}
		if (cmnd_name == "clearhis"){
			if(params.size() == 0){
				fstream file_to_clear;
				file_to_clear.open("history.txt", ios::in | ios::out);
				file_to_clear.clear();
				numbers.clear(); 
				update_file();
			}
		}
	}	
}

void open_file(string file_name){
	
	file_code.clear(); 
	ifstream file ; 
	
	file.open(file_name);
	
	Numbers num ; 
	string command ; 
	
	while(getline(file, command)){
		
		if (command == "exit();"){
			break ;
		}
		if (has_equals(command)){
			num.data = "";
			num.name = "";
			num = get_numbers(num, command) ; 
			if (check_is_null(num)){
			cout << "\nSpacing error!\n" ; 
			}
			else{
				file_code.push_back(command);
			}
		}else{
			diagnose_command(command);
			file_code.push_back(command);
		}
	}
	
	file.close();
}

void get_from_file(){
	
	string files[6] = {"add.txt", "sub.txt", "mul.txt", "div.txt", "pow.txt", "test.txt"};
	
	cout << "name of file:\n";
	string name_of_file; 
	
	cin >> name_of_file ;
	
	
	bool found = false ; 
	for(string in: files){
		if (name_of_file == in){
			cout << "****run " << in << "****" << endl ; 
			found = true ; 
			break;
		}
	}
	if (!found){
		cout << "SUCH FILE DOESN'T EXIST!\n" ; 
	}
	
	
	else{
		if(name_of_file == files[0]){
			open_file(files[0]); 
		}
		else if(name_of_file == files[1]){
			open_file(files[1]); 
		}
		else if(name_of_file == files[2]){
			open_file(files[2]); 
		}
		else if(name_of_file == files[3]){
			open_file(files[3]); 
		}
		else if(name_of_file == files[4]){
			open_file(files[4]); 
		}
		else if(name_of_file == files[5]){
			open_file(files[5]); 
		}
	}
}

void press_to_continue(){
	cout << "\n\npress any key to continue..." ; 
	getch() ;
}

void live_code(){
	
	bool quit = false ; 
	
	Numbers num ; 
	
	string command ; 
	
	while(!quit){
		cout << ">>> " ; 
		getline(cin >> ws, command) ; 
		
		if (command == "exit();"){
			quit = true ; 
			break ;
		}
		if (has_equals(command)){
			num.data = "";
			num.name = "";
			num = get_numbers(num, command) ; 
			if (check_is_null(num)){
			cout << "\nSpacing error!\n" ; 
			}
		}else{
			diagnose_command(command);
		}
	}
}

void view_history(){
	for(Numbers in: numbers){
		cout << in.name << " = " << in.data << endl ; 
	}
}

int main(){
	
	load_data();
	live_code(); 

	int choice ; 
	bool quit = false ; 
	
	while(!quit){
		system("cls") ; 
		cout << "1. start coding\n"; 
		cout << "2. Run via file\n"; 
		cout << "3. View history\n"; 
		cout << "4. Exit\n"; 
		cout << ">>> "; 
		cin >> choice ; 

		switch(choice){
			case 1: 
				live_code();
				press_to_continue();
				break;
			case 2: 
				get_from_file();
				press_to_continue();
				break;
			case 3:
				view_history();
				press_to_continue();
				break ; 
			case 4: quit = true;
				break;
			default: cout << "invalid input:/\n" ;
		}
	}
	return 0 ; 
}
