/***************************************
 * Author: Emilio E. G. Cantón Bermúdez
 * Date: 14/09/2019
***************************************/
#include "LanguageGenerator.h"

using namespace std;

LanguageGenerator::LanguageGenerator(){};

void LanguageGenerator::find_strings(string file)
{
	u_int t, n, m, N;
	ifstream input;

	input.open(file);
	input >> t;
	while (t)
	{
		input >> n >> m >> N;
		string temp_r_i;
		if (t < 1 || n < 1 || m <= 0 || N < 0)
		{
			cout << "Formato de documento incorrecto";
			exit(1);
		}
		string basec;
		while (n)
		{
			input >> basec;
			language.insert(pair<string, int>(basec, 0));
			--n;
		}

		while (m)
		{
			input >> temp_r_i;
			R.push_back(temp_r_i);
			--m;
		}
		cout << "Aplicando los siguientes pasos recursivos " << N << " veces: ";
		for (auto r_i : R)
		{
			cout << r_i << " ";
		}
		cout << '\n';
		applyRS(N);
		language.clear();
		R.clear();
		--t;
	}
}
void LanguageGenerator::applyRS(u_int N)
{
	for (size_t i = 1; i <= N; i++)
	{
		r(i);
	}

	print_language(N);
}
void LanguageGenerator::r(u_int N)
{
	vector<string> strings_from_recursive_step;
	for (auto rs : R)
	{
		vector<string> s_matches;
		for (size_t i = 0; i < rs.length(); i++)
		{
			for (size_t j = 0; j < sizeof(valid); j++)
			{
				if (valid[j] == rs[i])
				{
					stringstream ss;
					string s;
					ss << valid[j];
					ss >> s;
					s_matches.push_back(s);
				}
			}
		}
		vector<vector<string>> combinations = generate_combinations(s_matches);

		for (size_t i = 0; i < combinations.size(); i++)
		{
			string permutation = rs;
			for (size_t j = 0; j < s_matches.size(); j++)
			{
				// cout << "Searching for " + s_matches[j] + " in " + permutation <<'\n';
				int pos = permutation.find(s_matches[j]);
				while (pos != string::npos)
				{
					// cout << "Found at " << pos << ", replacing with " + combinations[i][j] << '\n';
					permutation.replace(pos, 1, combinations[i][j]);
					pos = permutation.find(s_matches[j]);
				}

				// cout << "Permutation -> " + permutation << '\n';
			}
			strings_from_recursive_step.push_back(permutation);
		}
	}
	for (auto s : strings_from_recursive_step)
	{
		s = replace_lambda(s);
		language.insert(pair<string, int>(s, N));
	}
}
string LanguageGenerator::replace_lambda(string s)
{
	// cout << "Entered " + s;
	size_t pos = s.find("L");
	while (pos != string::npos)
	{
		s.replace(pos, 1, "");
		pos = s.find("L", pos);
	}
	// cout << " and replaced with " << s << '\n';
	return s;
}
vector<vector<string>> LanguageGenerator::generate_combinations(vector<string> matches)
{
	int n_combinations = pow(language.size(), matches.size());
	vector<vector<string>> c(n_combinations, vector<string>(matches.size()));
	vector<string> l;
	for (auto const kv : language)
	{
		l.push_back(kv.first);
	}
	int loops = n_combinations / language.size();
	int curr_word = 0;
	for (size_t j = 0; j < matches.size(); j++)
	{
		for (size_t i = 0; i < n_combinations; i++)
		{
			if (i % loops == 0 && i != 0)
			{
				curr_word = (curr_word + 1) % language.size();
			}
			c[i][j] = l[curr_word];
		}
		loops /= language.size();
	}
	return c;
}
void LanguageGenerator::print_language(u_int N)
{
	vector<vector<string>> ordered_language(N + 1);
	int line = ceil(language.size() / (double)(language.size() / 6));

	for (auto const kv : language)
	{
		ordered_language[kv.second].push_back(kv.first);
	}

	u_int strings_printed = 1;
	cout << "{"
		 << "\n\t";
	for (size_t i = 0; i < ordered_language.size(); i++)
	{
		cout << i << ":"
			 << "\n\t  "
			 << "["
			 << "\n\t\t";
		for (size_t j = 0; j < ordered_language[i].size(); j++)
		{
			if (ordered_language[i].size() - 1 == j)
			{
				cout << ordered_language[i][j] << "\n\t";
			}
			else if ((j + 1) % line == 0)
			{
				cout << ordered_language[i][j] << ",\n\t\t";
			}
			else
			{
				cout << ordered_language[i][j] << ", ";
			}
		}
		cout << "\r\t  "
			 << "]"
			 << "\n\t";
	}
	cout << "\r\r"
		 << "}" << '\n';
}