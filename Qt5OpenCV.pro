QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TEMPLATE = subdirs

SUBDIRS = \
          src \
          example

# where to find the sub projects - give the folders
src.subdir= src
example.subdir= example
# what subproject depends on others
example.depends = src
