from tkinter import *
from tkinter import messagebox
from math import *

last_func = "x"


def draw_axes(a=0):
    canvas.delete("all")
    line = canvas.create_line(0, canvas.winfo_height() / 2,
                              canvas.winfo_width(), canvas.winfo_height() / 2, fill="black", arrow='last',
                              arrowshape=(7, 7, 5), width=2)
    line = canvas.create_line(canvas.winfo_width() / 2, 0,
                              canvas.winfo_width() / 2, canvas.winfo_height(), fill="black", arrow='first',
                              arrowshape=(7, 7, 5), width=2)
    space = int(axes_scale.get())

    i = 0
    while canvas.winfo_width() / 2 + space * i <= canvas.winfo_width():
        i += 1
        line = canvas.create_line(canvas.winfo_width() // 2 + space * i, 0,
                                  canvas.winfo_width() // 2 + space * i, canvas.winfo_height(), width=1, fill="gray")
        line = canvas.create_line(canvas.winfo_width() // 2 - space * i, 0,
                                  canvas.winfo_width() // 2 - space * i, canvas.winfo_height(), width=1, fill="gray")

    i = 0
    while canvas.winfo_height() / 2 + space * i <= canvas.winfo_height():
        i += 1
        line = canvas.create_line(0, canvas.winfo_height() // 2 + space * i,
                                  canvas.winfo_width(), canvas.winfo_height() // 2 + space * i, width=1, fill="gray")
        line = canvas.create_line(0, canvas.winfo_height() // 2 - space * i,
                                  canvas.winfo_width(), canvas.winfo_height() // 2 - space * i, width=1, fill="gray")

    draw_function(1)


def draw_function(a=0):
    global last_func
    y = (function_entry.get())
    if y.strip() == "":
        messagebox.showerror("Ошибка", "Поле функции не может быть пустым")
        return 0

    if a == 0:
        last_func = y
        draw_axes(0)

    else:
        y = last_func

    try:
        x = -canvas.winfo_width() / int(axes_scale.get()) / 2
        lasty = (eval(y)) * int(axes_scale.get())
        last_x = x * int(axes_scale.get())
    except Exception:
        x = 0
        last_x = 0
        lasty = (eval(y)) * int(axes_scale.get())

    while x <= canvas.winfo_width() / int(axes_scale.get()) / 2 + 1:
        try:
            now_y = (eval(y)) * int(axes_scale.get())
            line = canvas.create_line(last_x, (canvas.winfo_height() - lasty),
                                      x * int(axes_scale.get()), (canvas.winfo_height() - now_y), width=3,
                                      fill="darkred")
            canvas.move(line, canvas.winfo_width() // 2, -canvas.winfo_height() // 2)
            lasty = now_y
            last_x = x * int(axes_scale.get())
        except ZeroDivisionError:
            pass
        except TclError:
            x = 0
            last_x = 0
            lasty = (eval(y)) * int(axes_scale.get())
        except ValueError:
            pass
        finally:
            x += 0.1


def window_resize(event):
    draw_axes()


def help_info():
    messagebox.showinfo("Помощь",
                        'ВОЗМОЖНОСТИ:\nСделайте двойной щелчок ПКМ по графику,\nчтобы поставить '
                        'точку.\n\nФУНКЦИИ:\nВозведение в степень -> **\nДеление -> /\nСинус -> sin(x)\nКосинус -> '
                        'cos(x)\nТангенс -> tan(x)\n\nУКАЗАНИЯ:\nНаслаждайтесь.')


def inform():
    messagebox.showinfo("О программе",
                        "\nПрограмма для построения графиков.\n\n\n                           Автор: Шубин Илия")


def draw_point(event=0):
    draw_axes()

    point_x = event.x
    point_y = event.y
    canvas.create_oval(event.x - 3, event.y - 3, event.x + 3, event.y + 3, fill='red')

    point_label['text'] = "({0:.1f};{1:.1f})".format((event.x - canvas.winfo_width() // 2) / axes_scale.get(),
                                                     -(event.y - canvas.winfo_height() // 2) / axes_scale.get())


window = Tk()
menu = Menu(window)
window.config(bg='lightBlue', menu=menu)
window.title("Программа для построения графиков")
window.geometry('800x500')

helpmenu = Menu(menu, tearoff=0)
helpmenu.add_command(label="Помощь", command=help_info)
helpmenu.add_command(label="О программе", command=inform)
menu.add_cascade(label='Справка', menu=helpmenu)

leftFrame = Frame(window, width=300, bg="lightblue", height=600, relief='flat')
rightFrame = Frame(window, bg="lightblue", width=500, relief='flat')
leftFrame.pack(side="left", fill=Y)
rightFrame.pack(side="right", fill=BOTH, expand=1)

axes_scale = Scale(leftFrame, font=('Arial', 16), bg='lightgray', fg='black', relief='flat',
                   highlightbackground="black",
                   highlightthickness=1, from_=10, to=200, command=draw_axes, orient=HORIZONTAL, resolution=20)
axes_scale.set(60)
axes_scale.place(x=50, y=250 - 75, width=200)

canvas = Canvas(rightFrame, bg="lightgray", relief='flat', highlightbackground="black", highlightthickness=2)
canvas.pack(fill=BOTH, expand=1, padx=10, pady=10)
canvas.bind('<Configure>', window_resize)
canvas.bind('<Double-Button-1>', draw_point)

function_label = Label(leftFrame, text="y=", font="Arial, 16", bg='lightgray', relief='solid',
                       highlightbackground="black", borderwidth=1, anchor="w")
function_label.place(x=50, y=250, width=201, height=30)

function_entry = Entry(leftFrame, font=('Arial', 16), bg='lightgray', fg='black', justify='left')
function_entry.insert(0, "x")
function_entry.place(x=80, y=251, width=170, height=28)

function_button = Button(leftFrame, text='построить', font=('Arial', 14), bg='lightGray', fg='black',
                         command=draw_function)
function_button.place(x=95, y=250 + 35, width=100, height=30)

point_label = Label(leftFrame, text="(x;y)", font="Arial, 16", bg='lightgray', relief='solid',
                    highlightbackground="black", borderwidth=1)
point_label.place(x=90, y=75, width=120, height=30)

window.mainloop()