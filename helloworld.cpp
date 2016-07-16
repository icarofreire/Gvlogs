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

#include "helloworld.h"
#include <iostream>
#include <vector>
using namespace std;

HelloWorld::HelloWorld()
: m_button("Hello World"),   // creates a new button with label "Hello World".
  m_VBox(Gtk::ORIENTATION_VERTICAL),
  m_Button_Quit("Fechar")
{
  // Sets the border width of the window.
  set_border_width(10);
  set_title("Visualizador de logs");
  set_default_size(400, 400);

  add_arquivo.set_label("Adicionar arquivo");
  remover_aba.set_label("Remover Aba");


  // --
  // Gtk::TreeView *treeview = Gtk::manage(new Gtk::TreeView);
  //   treeview.set_hexpand(true);
  //   treeview.set_vexpand(true);
  //
  // refTreeModel = Gtk::ListStore::create(columns);
  //   treeview.set_model(refTreeModel);
  //   treeview.append_column("Cnt", columns.col_cnt);
  //   treeview.append_column("Text", columns.col_text);
  //   add_lista("teste 1");
  //   add_lista("teste 2");
  // add_lista_em_aba();
  // add_lista_em_aba();
  // --


  add(m_VBox);

 //Add the Notebook, with the button underneath:
 m_Notebook.set_border_width(10);
 m_VBox.pack_start(m_Notebook);
 m_VBox.pack_start(m_ButtonBox, Gtk::PACK_SHRINK);

 m_ButtonBox.pack_start(add_arquivo, Gtk::PACK_SHRINK);
 m_ButtonBox.pack_start(remover_aba, Gtk::PACK_SHRINK);
 m_ButtonBox.pack_start(m_Button_Quit, Gtk::PACK_SHRINK);

 m_Button_Quit.signal_clicked().connect(sigc::mem_fun(*this,
             &HelloWorld::on_button_quit) );

 add_arquivo.signal_clicked().connect(sigc::mem_fun(*this,
             &HelloWorld::evento_botao_add_arquivo) );

 remover_aba.signal_clicked().connect(sigc::mem_fun(*this,
             &HelloWorld::evento_botao_remover_aba) );


 //Add the Notebook pages:
 add_aba("Primeiro");

 m_Notebook.signal_switch_page().connect(sigc::mem_fun(*this,
             &HelloWorld::on_notebook_switch_page) );

 show_all_children();

}

HelloWorld::~HelloWorld()
{
}

void HelloWorld::on_button_clicked()
{
  std::cout << "Hello World" << std::endl;
}

void HelloWorld::evento_botao_add_arquivo()
{
  add_aba("xip");
  std::cout << "Add um novo arquivo" << std::endl;
}

void HelloWorld::evento_botao_remover_aba()
{
  int aba = m_Notebook.get_current_page();
  std::cout << "remover aba: " << aba << std::endl;
  if( m_Notebook.get_n_pages() > 1 ){
    m_Notebook.remove_page(aba);
  }
}

void HelloWorld::on_button_quit()
{
  hide();
}

void HelloWorld::on_notebook_switch_page(Gtk::Widget* /* page */, guint page_num)
{
  std::cout << "Switched to tab with index " << page_num << std::endl;
  //You can also use m_Notebook.get_current_page() to get this index.
}

void HelloWorld::add_aba(Glib::ustring titulo_da_aba)
{
  int indice_nova_aba = m_Notebook.get_n_pages();

  vector<Glib::ustring> linhas;
  for(int i=0; i<100; i++){
    linhas.push_back("item ");
  }

  add_lista_em_aba(indice_nova_aba, linhas);
  m_Notebook.append_page(scroll[indice_nova_aba], titulo_da_aba);
  lista.show_all();
  show_all_children();
}
