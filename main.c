//
//  main.c
//  PWDM
//
//  Created by Eric on 16-2-19.
//  Copyright (c) 2016年 Bakantu Eric. All rights reserved.
//

#include <stdio.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>

#define N_MAX 256

GtkWidget *window,*frame,*get_pwd,*sl_input,*sl_spec,*sl_output,*s_input,*s_spec,*ss_output;

void cal_pwd(void);

void cal_pwd(void){
    char *i_buf,*s_buf,o_buf[N_MAX];
    unsigned long i_len,s_len,i;
    unsigned long long i_num = 0,s_num = 0;
    i_buf = (gchar *) gtk_entry_get_text(GTK_ENTRY(s_input));
    s_buf = (char *) gtk_entry_get_text(GTK_ENTRY(s_spec));
    i_len = strlen(i_buf);
    s_len = strlen(s_buf);
    
    for (i = 0; i < i_len; i++) {
        i_num += (unsigned long long) i_buf[i];
        i_num *= 10;
    }
    for (i = 0; i < s_len; i++) {
        s_num += (unsigned long long) s_buf[i];
        s_num *= 10*i_len;
    }
    
    i_num |= ~(~s_num&(~i_num));
    
    sprintf(o_buf, "%llx",i_num);
    
    gtk_label_set_text(GTK_LABEL(ss_output), o_buf);
}

int main(int argc, char * argv[]) {
    // insert code here...
    gtk_init(&argc, &argv);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "PWDM 2");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    
    frame = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), frame);

    get_pwd = gtk_button_new_with_label("生成密码");
    gtk_widget_set_size_request(get_pwd, 290, 30);
    gtk_fixed_put(GTK_FIXED(frame), get_pwd, 5, 150);
    
    sl_input = gtk_label_new("输入码: ");
    gtk_widget_set_size_request(sl_input, 60, 30);
    gtk_fixed_put(GTK_FIXED(frame), sl_input, 5, 5);
    
    s_input = gtk_entry_new();
    gtk_widget_set_size_request(s_input, 230, 30);
    gtk_fixed_put(GTK_FIXED(frame), s_input, 65, 5);
    gtk_entry_set_max_length(GTK_ENTRY(s_input), 18);
    
    sl_spec = gtk_label_new("特征码: ");
    gtk_widget_set_size_request(sl_spec, 60, 30);
    gtk_fixed_put(GTK_FIXED(frame), sl_spec, 5, 60);

    
    s_spec = gtk_entry_new();
    gtk_widget_set_size_request(s_spec, 230, 30);
    gtk_fixed_put(GTK_FIXED(frame), s_spec, 65, 60);
    gtk_entry_set_max_length(GTK_ENTRY(s_spec), 6);
    
    sl_output = gtk_label_new("加密码: ");
    gtk_widget_set_size_request(sl_output, 60, 30);
    gtk_fixed_put(GTK_FIXED(frame), sl_output, 5, 110);
    
    ss_output = gtk_label_new("");
    gtk_widget_set_size_request(ss_output, 230, 30);
    gtk_fixed_put(GTK_FIXED(frame), ss_output, 65, 110);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(get_pwd, "clicked", G_CALLBACK(cal_pwd), NULL);

    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}
