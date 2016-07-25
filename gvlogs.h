//$Id: helloworld.h 2 2003-01-21 13:41:59Z murrayc $ -*- c++ -*-

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

#ifndef GTKMM_EXAMPLE_HELLOWORLD_H
#define GTKMM_EXAMPLE_HELLOWORLD_H

#include <gtkmm.h>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#define MAXIMO_ABAS 100

class Gvlogs : public Gtk::Window
{
	
	public:
		Gvlogs();
		virtual ~Gvlogs();
	
	protected:
		//Signal handlers:
		void evento_botao_add_arquivo();
		void evento_botao_remover_aba();
		void evento_trocou_aba(Gtk::Widget* page, guint page_num);
		void on_button_quit();
		
		//Member widgets:
		Gtk::Button m_button;
		Gtk::Button add_arquivo;
		Gtk::Button remover_aba;
		
		Glib::ustring titulo_primeira_aba = "File.log";
		int altura = 700;
		int largura = 1000;
		std::string nome_arquivo;
		std::string caminho_completo_arquivo;
		
		//Child widgets:
		Gtk::Box m_VBox;
		Gtk::Notebook m_Notebook;
		Gtk::ListBox lista;
		Gtk::ScrolledWindow scroll[MAXIMO_ABAS];
		Gtk::TreeView treeview[MAXIMO_ABAS];
		Gtk::ButtonBox m_ButtonBox;
		Gtk::Button m_Button_Quit;
		
		// metodos
		void add_aba(Glib::ustring, vector<Glib::ustring>*);
		void abrir_seletor_de_arquivos();
		vector<Glib::ustring> linhas_arquivo(std::string&);
		void vector_delete(int);
		int add_lista_em_aba(vector<Glib::ustring>&);
		
		class ModelColumns : public Gtk::TreeModel::ColumnRecord
		{
			public:
			ModelColumns()
			{ add(col_cnt); add(col_text); }
		
			int rowcount = 0;
			Gtk::TreeModelColumn<int> col_cnt;
			Gtk::TreeModelColumn<Glib::ustring> col_text;
		};

		void add_lista(ModelColumns&, Glib::RefPtr<Gtk::ListStore>&, Glib::ustring);
		//~ void add_lista(ModelColumns& columns, Glib::RefPtr<Gtk::ListStore>& refTreeModel, Glib::ustring conteudo)
		//~ {
			//~ columns.rowcount++;
			//~ Gtk::TreeModel::Row row = *(refTreeModel->append());
			//~ row[columns.col_cnt] = columns.rowcount;
			//~ row[columns.col_text] = conteudo;
		//~ }
		
		//~ int add_lista_em_aba(vector<Glib::ustring>& linhas)
		//~ {
			//~ int indice_aba = 0;
			//~ for(int i=0; i<MAXIMO_ABAS; i++){
				//~ if(
					//~ scroll[i].get_parent() == nullptr && 
					//~ treeview[i].get_parent() == nullptr
				//~ ){
					//~ indice_aba = i; 
					//~ break;
				//~ }
			//~ }
			  //~ 
			//~ scroll[ indice_aba ].set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_ALWAYS);
			//~ treeview[ indice_aba ].set_hexpand(true);
			//~ treeview[ indice_aba ].set_vexpand(true);
			//~ 
			//~ ModelColumns columns;
	        //~ Glib::RefPtr<Gtk::ListStore> refTreeModel;
	        //~ 
			//~ refTreeModel = Gtk::ListStore::create(columns);
			//~ treeview[ indice_aba ].set_model(refTreeModel);
			//~ treeview[ indice_aba ].append_column("Cnt", columns.col_cnt);
			//~ treeview[ indice_aba ].append_column("Text", columns.col_text);
			//~ 
			//~ for(vector<Glib::ustring>::iterator i = linhas.begin(); i != linhas.end(); i++){
				//~ add_lista(columns, refTreeModel, *i );
			//~ }
			//~ scroll[ indice_aba ].add( treeview[ indice_aba ] );
			//~ columns.rowcount = 0;
			//~ return indice_aba;
		//~ }
};

#endif // GTKMM_EXAMPLE_HELLOWORLD_H
