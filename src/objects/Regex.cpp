#include "Regex.h"

Lexem::Lexem(Type type, char symbol) 
	: type(type), symbol(symbol) {}

vector<Lexem> Regex::parse_string(string str) {
	vector<Lexem> lexems;
	lexems = {};

	auto is_symbol = [](char c) {
		return c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z';
	};

	for (const char& c : str) {
		Lexem lexem;
		switch (c) {
		case '(':
			lexem.type = Lexem::parL;
			break;
		case ')':
			lexem.type = Lexem::parR;
			break;
		case '|':
			lexem.type = Lexem::alt;
			break;
		case '*':
			lexem.type = Lexem::star;
			break;
		default:
			if (is_symbol(c)) {
				lexem.type = Lexem::symb;
				lexem.symbol = c;
			}
			else {
				lexem.type = Lexem::error;
				lexems = {};
				lexems.push_back(lexem);
				return lexems;
			}
			break;
		}

		if (lexems.size() && (
			// Lexem left
			lexems.back().type == Lexem::symb ||
			lexems.back().type == Lexem::star ||
			lexems.back().type == Lexem::parR) && (
			// Lexem right
			lexem.type == Lexem::symb ||
			lexem.type == Lexem::parL)) {

			// We place . between
			lexems.push_back({Lexem::conc});
		}

		lexems.push_back(lexem);
	}
	return lexems;
}

Regex* Regex::scan_conc(vector<Lexem> lexems, int index_start, int index_end) {
	Regex* l, *r, *p;
    p = NULL;
    int b_o = 0;
    for (int i = index_start; i < index_end; i++)
    {   
        if (lexems[i].type == Lexem::parL) { //LEFT_BRACKET
            b_o ++;
        }
        if (lexems[i].type == Lexem::parR) { //RIGHT_BRACKET
            b_o--;
        }
        if (lexems[i].type == Lexem::conc && b_o == 0) {
            
            l = expr(lexems, index_start, i);
            r = expr(lexems, i+1, index_end);

			if (l->type == Regex::error && r->type == Regex::error) { //Проверка на адекватность)
				return p;
			}

            p = new Regex; //(Node*)malloc(sizeof(Node));
            p->term_l = l;
            p->term_r = r;
            p->symbol = lexems[i];
			p->type = Regex::conc;
            return p;
        }
    }
	return p;
}

Regex* Regex::scan_star(vector<Lexem> lexems, int index_start, int index_end) {
	Regex* l, *r, *p;
    p = NULL;
    int b_o = 0;
    for (int i = index_start; i < index_end; i++)
    {   
        if (lexems[i].type == Lexem::parL) { //LEFT_BRACKET
            b_o ++;
        }
        if (lexems[i].type == Lexem::parR) { //RIGHT_BRACKET
            b_o--;
        }
        if (lexems[i].type == Lexem::star && b_o == 0) {
            
            l = expr(lexems, index_start, i);

            if (l->type == Regex::error) {
				return p;
			}

            p = new Regex; //(Node*)malloc(sizeof(Node));
            p->term_l = l;
			
            p->term_r = NULL;
            p->symbol = lexems[i];
			p->type = Regex::star;
            return p;
        }
    }
	return p;
}

Regex* Regex::scan_alt(vector<Lexem> lexems, int index_start, int index_end) {
	Regex* l, *r, *p;
    p = NULL;
    int b_o = 0;
    for (int i = index_start; i < index_end; i++)
    {   
        if (lexems[i].type == Lexem::parL) { //LEFT_BRACKET
            b_o ++;
        }
        if (lexems[i].type == Lexem::parR) { //RIGHT_BRACKET
            b_o--;
        }
        if (lexems[i].type == Lexem::alt && b_o == 0) {
            
            l = expr(lexems, index_start, i);
            r = expr(lexems, i+1, index_end);

			if (l->type == Regex::error && r->type == Regex::error) { //Проверка на адекватность)
				return p;
			}

            p = new Regex; //(Node*)malloc(sizeof(Node));

            p->term_l = l;
            p->term_r = r;
            p->symbol = lexems[i];
			p->type = Regex::alt;
            return p;
        }
    }
	return p;
}

Regex* Regex::scan_symb(vector<Lexem> lexems, int index_start, int index_end) {
    Regex *p = NULL;
	if (lexems[index_start].type != Lexem::symb) {
		return p;
	}
    p = new Regex; //(Node*)malloc(sizeof(Node));
    p->symbol = lexems[index_start];
	p->type = Regex::symb;
    return p;
}

Regex* Regex::scan_par(vector<Lexem> lexems, int index_start, int index_end) {
	Regex* l, *r, *p;
    p = NULL;
    int b_o = 0;

	if (lexems[index_start].type != Lexem::parL |
		lexems[index_end-1].type != Lexem::parR) {
		return p;
	}
	p = expr(lexems, index_start + 1, index_end - 1);
	return p;
}
Regex* Regex::expr(vector<Lexem> lexems, int index_start, int index_end) {
	Regex* p;
	p = scan_alt(lexems, index_start, index_end);
	if (!p) {
		p = scan_conc(lexems, index_start, index_end);
	}
	if (!p) {
		p = scan_star(lexems, index_start, index_end);
	}
	if (!p) {
		p = scan_symb(lexems, index_start, index_end);
	}
	if (!p) {
		p = scan_par(lexems, index_start, index_end);
	}
	if (!p) {
		p = new Regex;
		p->type = Regex::error;
	}
	
	return p;
}
Regex::Regex(){}

Regex::Regex(string str) {
	vector<Lexem> l;
	l = parse_string(str);
	Regex* root = expr(l, 0, l.size());
	*this = *root;
	delete root;
	if (this->type == Regex::error) {
		cout << l.size() <<" ERROR\n";
	}
}

Regex* Regex::copy() {
		Regex* c = new Regex();
		c->type = type;
		c->symbol = symbol;
		if (/*type != regex_cell_state::epsilon && У нас нет лексемы пустоты*/
			type != Regex::symb) {
			c->term_l = term_l->copy();
			if (type != Regex::conc)
				c->term_r= term_r->copy();
		}
		return c;
	}

void Regex::clear() {
		if (term_l != nullptr) {
			term_l->clear();
			delete term_l;
		}
		if (term_r != nullptr) {
			term_r->clear();
			delete term_r;	
		}
	}

void Regex::pre_order_travers() {
    if (this) {
		if (this->symbol.symbol) {
        	cout << this->symbol.symbol << " ";
		} else {
			cout << this->type << " ";
		}
		this->term_l->pre_order_travers();
		this->term_r->pre_order_travers();
    }
}

string Regex::to_txt() {
	return string();
}
