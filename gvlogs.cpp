//$Id: helloworld.cc 836 2007-05-09 03:02:38Z jjongsma $ -*- c++ -*-

/* gtkmm example Copyright (C) 2002 gtkmm development team
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include "gvlogs.h"
#include <iostream>
#include <vector>
using namespace std;

Gvlogs::Gvlogs():
	m_button("Hello World"),   // creates a new button with label "Hello World".
	m_VBox(Gtk::ORIENTATION_VERTICAL),
	m_Button_Quit("Sair")
{
	// Sets the border width of the window.
	set_border_width(10);
	set_title("Visualizador de logs");
	set_default_size(largura, altura);
	
	add_arquivo.set_label("Adicionar arquivo");
	remover_aba.set_label("Remover Aba");
	
	add(m_VBox);
	
	//Add the Notebook, with the button underneath:
	m_Notebook.set_border_width(10);
	m_VBox.pack_start(m_Notebook);
	m_VBox.pack_start(m_ButtonBox, Gtk::PACK_SHRINK);
	
	m_ButtonBox.pack_start(add_arquivo, Gtk::PACK_SHRINK);
	m_ButtonBox.pack_start(remover_aba, Gtk::PACK_SHRINK);
	m_ButtonBox.pack_start(m_Button_Quit, Gtk::PACK_SHRINK);
	
	m_Button_Quit.signal_clicked().connect(sigc::mem_fun(*this, &Gvlogs::on_button_quit) );
	
	add_arquivo.signal_clicked().connect(sigc::mem_fun(*this, &Gvlogs::evento_botao_add_arquivo) );
	
	remover_aba.signal_clicked().connect(sigc::mem_fun(*this, &Gvlogs::evento_botao_remover_aba) );
	
	m_Notebook.signal_switch_page().connect(sigc::mem_fun(*this, &Gvlogs::evento_trocou_aba) );
	
	vector<Glib::ustring> l__;
	// add_aba(titulo_primeira_aba, &l__);
	
	
	show_all_children();

}

Gvlogs::~Gvlogs()
{
}

void Gvlogs::evento_trocou_aba(Gtk::Widget* page, guint page_num)
{
  remover_aba.set_label("Remover '" + m_Notebook.get_tab_label_text(*page) + "'");
}

void Gvlogs::evento_botao_add_arquivo()
{
	abrir_seletor_de_arquivos();
	if( (!caminho_completo_arquivo.empty()) && (!nome_arquivo.empty()) )
	{
		vector<Glib::ustring> linhas = linhas_arquivo(caminho_completo_arquivo);
		int tam_max = 30;
		if( nome_arquivo.size() > tam_max ){
			nome_arquivo = nome_arquivo.substr(0,tam_max-3)+"...";
		}
		add_aba(nome_arquivo, &linhas);
	}
}

void Gvlogs::evento_botao_remover_aba()
{
	int aba = m_Notebook.get_current_page();
	if( m_Notebook.get_n_pages() > 1 ){
		m_Notebook.remove_page(aba);
	}
}

void Gvlogs::on_button_quit()
{
	hide();
}

void Gvlogs::add_aba(Glib::ustring titulo_da_aba, vector<Glib::ustring>* linhas)
{
	int indice_nova_aba = m_Notebook.get_n_pages();
	int scroll_aba = add_lista_em_aba(*linhas);
	
	m_Notebook.append_page( scroll[scroll_aba], titulo_da_aba);
	lista.show_all();
	show_all_children();
	m_Notebook.set_current_page(indice_nova_aba);
}

void Gvlogs::abrir_seletor_de_arquivos()
{
	Gtk::FileChooserDialog dialog("Please choose a file", Gtk::FILE_CHOOSER_ACTION_OPEN);
	dialog.set_transient_for(*this);
	
	//Add response buttons the the dialog:
	dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
	dialog.add_button("_Open", Gtk::RESPONSE_OK);
	
	auto filter_any = Gtk::FileFilter::create();
	filter_any->set_name("Any files");
	filter_any->add_pattern("*");
	dialog.add_filter(filter_any);
	
	//Show the dialog and wait for a user response:
	int result = dialog.run();
	
	//Handle the response:
	std::string filename = "";
	switch(result)
	{
		case(Gtk::RESPONSE_OK):
		{
			//~ std::cout << "Open clicked." << std::endl;
			auto arq = dialog.get_file();
			nome_arquivo = arq->get_basename();
			//Notice that this is a std::string, not a Glib::ustring.
			filename = dialog.get_filename();
			caminho_completo_arquivo = filename;
		break;
		}
		case(Gtk::RESPONSE_CANCEL):
		{
			//~ std::cout << "Cancel clicked." << std::endl;
			break;
		}
		default:
		{
			//~ std::cout << "Unexpected button clicked." << std::endl;
			break;
		}
	}
}

vector<Glib::ustring> Gvlogs::linhas_arquivo(std::string& arquivo)
{
	std::ifstream file(arquivo);
	std::string str;
	vector<Glib::ustring> linhas;
	while (std::getline(file, str))
	{
		linhas.push_back(str);
	}
	return linhas;
}

void Gvlogs::add_lista(ModelColumns& columns, Glib::RefPtr<Gtk::ListStore>& refTreeModel, Glib::ustring conteudo)
{
	columns.rowcount++;
	Gtk::TreeModel::Row row = *(refTreeModel->append());
	row[columns.col_cnt] = columns.rowcount;
	row[columns.col_text] = conteudo;
}

int Gvlogs::add_lista_em_aba(vector<Glib::ustring>& linhas)
{
	int indice_aba = 0;
	for(int i=0; i<MAXIMO_ABAS; i++){
		if(
			scroll[i].get_parent() == nullptr && 
			treeview[i].get_parent() == nullptr
		){
			indice_aba = i; break;
		}
	}
	  
	scroll[ indice_aba ].set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_ALWAYS);
	treeview[ indice_aba ].set_hexpand(true);
	treeview[ indice_aba ].set_vexpand(true);
	
	ModelColumns columns;
	Glib::RefPtr<Gtk::ListStore> refTreeModel;
	
	refTreeModel = Gtk::ListStore::create(columns);
	treeview[ indice_aba ].set_model(refTreeModel);
	treeview[ indice_aba ].append_column("Cnt", columns.col_cnt);
	treeview[ indice_aba ].append_column("Text", columns.col_text);
	
	for(vector<Glib::ustring>::iterator i = linhas.begin(); i != linhas.end(); i++){
		add_lista(columns, refTreeModel, *i );
	}
	scroll[ indice_aba ].add( treeview[ indice_aba ] );
	columns.rowcount = 0;
	return indice_aba;
}
