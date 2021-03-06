/*
    Copyright 2012 Charit� Universit�tsmedizin Berlin, Institut f�r Radiologie

	This file is part of KardioPerfusion.

    KardioPerfusion is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    KardioPerfusion is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with KardioPerfusion.  If not, see <http://www.gnu.org/licenses/>.

    Diese Datei ist Teil von KardioPerfusion.

    KardioPerfusion ist Freie Software: Sie k�nnen es unter den Bedingungen
    der GNU General Public License, wie von der Free Software Foundation,
    Version 3 der Lizenz oder (nach Ihrer Option) jeder sp�teren
    ver�ffentlichten Version, weiterverbreiten und/oder modifizieren.

    KardioPerfusion wird in der Hoffnung, dass es n�tzlich sein wird, aber
    OHNE JEDE GEW�HRLEISTUNG, bereitgestellt; sogar ohne die implizite
    Gew�hrleistung der MARKTF�HIGKEIT oder EIGNUNG F�R EINEN BESTIMMTEN ZWECK.
    Siehe die GNU General Public License f�r weitere Details.

    Sie sollten eine Kopie der GNU General Public License zusammen mit diesem
    Programm erhalten haben. Wenn nicht, siehe <http://www.gnu.org/licenses/>.
*/

#ifndef KardioPerfusion_H
#define KardioPerfusion_H


#include <QMainWindow>
#include <QObject>
#include "vtkSmartPointer.h"    // Required for smart pointer internal ivars.
//#include "vtkImageViewer2.h"
#include "ctimagetreemodel.h"
#include "binaryimagetreeitem.h"
#include "ctimagetreeitem.h"
#include <qitemselectionmodel.h>
//#include "tacdialog.h"
#include <QMouseEvent>
#include "mytabwidget.h"
//#include "mmid4Analyzer.h"
#include "maxSlopeAnalyzer.h"
#include "realimagetreeitem.h"


#define VTK_CREATE(type, name) \
  vtkSmartPointer<type> name = vtkSmartPointer<type>::New()

// Forward Qt class declarations
class Ui_KardioPerfusion;
class DicomSelectorDialog;
class MultiPlanarReformatWidget;
class QwtPlotMarker;
class QwtPlotGrid;
class QwtPlotPicker;
class vtkLookupTable;

/*! \class KardioPerfusion KardioPerfusion.h "KardioPerfusion.h"
 *  \brief This is the main class for the graphical user interface.
 *
 */
class KardioPerfusion : public QMainWindow
{
	Q_OBJECT

	public:

	//! default Constructor of the class
	KardioPerfusion(); 
	//! Deconstructor of the class
	~KardioPerfusion();

//  void loadFile(QString fname);

	///Set the selected files to the SelectorDialog
	/*! 
	\param names contains the filenames to the images
	*/
	void setFiles(const QStringList &names);

	public slots:

	///Action to be taken upon file open
	virtual void slotOpenFile();
	///Action to exit the application
	virtual void slotExit();
	///Action to save a project
	void on_actionSave_Project_triggered();
      
	///Action to load a project
	void on_actionOpen_Project_triggered();
	
	//void on_treeView_doubleClicked(const QModelIndex &index);

	///Action for clicking on treeView.
	/*! 
	\param index contains the clicked index.
	*/
	void on_treeView_clicked(const QModelIndex &index);
	///Action for double clicking on treeview.
	/*!
	\param index contains the double clicked index.
	*/
	void on_treeView_doubleClicked(const QModelIndex &index);

	///Action for changing the selection of the treeView.
	/*! 
	\param selected contains the selected elements.
	\param deselected contains the deselected elements.
	*/
	void onSelectionChanged(const QItemSelection & selected, const QItemSelection & deselected);
	///Action for clicking on Draw-Button.
	void on_btn_draw_clicked();
	///Action for clicking on RegionGrow-Button.
	void on_btn_regionGrow_clicked();
	///Action for clicking on Erode-Button.
	void on_btn_erode_clicked();
	///Action for clicking on Erode-Button.
	void on_btn_dilate_clicked();
//	void on_btn_cannyEdges_clicked();
	///Action for clicking on Analyse-Button.
	void on_btn_analyse_clicked();
	///Action for clicking on PerfusionMap-Button
	void on_btn_perfusionMap_clicked();
	///Action for double clicking on a mprWidget.
	void mprWidget_doubleClicked(MultiPlanarReformatWidget &w);
	///Action for double clicking on a mytabwidget.
	void tabWidget_doubleClicked(MyTabWidget &w);
	///Slot for the contextmenu of the treeView.
	/*! 
	\param pos contains the position of the contextmenu.
	*/
	void treeViewContextMenu(const QPoint &pos);
	///creates a segment for selected image.
	void createSegmentForSelectedImage();
	///changes the color for the selected item.
	void changeColorForSelectedSegment();
	///removes a selected Image from the image model.
	void removeSelectedImages();
	///Slot will be called, if the value of the startSlider has changed.
	void sliderStartValue_changed();
	///Slot will be called, if the value of the endSlider has changed.
	void sliderEndValue_changed();
	///Slot will be called, if the table was clicked.
	void tableGamma_clicked(const QModelIndex & index);
	///Slot will be called, if the checkbutton was toggled.
	void cb_enableGamma_toggled();
	///Slot will be calles, if the button was pressed
	void on_btn_arteryInput_selected(const SegmentInfo *segment);
	///Slot will be called, if the slider value has changed
	void slider_opacity_changed();
	///Renames a selected item
	void renameTreeviewItem();
protected:
	///clears pending actions
    void clearPendingAction();

protected slots:

private:
	///Get selected TreeView-Item
	/*! 
	\return a pointer to the selected BinaryImageTreeItem
	*/
	BinaryImageTreeItem *focusSegmentFromSelection(void);
	typedef std::auto_ptr<DicomSelectorDialog> DicomSelectorDialogPtr;
	//vtkSmartPointer<vtkImageViewer2> m_pViewer[4];

    /// Designer form
    Ui_KardioPerfusion *ui;

	///load selected Dicom-File
	/*! 
	\param dicomSelector contains a pointer to the Selector-Dialog
	*/
	void loadDicomData(DicomSelectorDialogPtr dicomSelector);
	///sets a given Image to the output view
	/*! 
	\param imageItem contains the image that should be visualized
	*/
	void setImage(const CTImageTreeItem *imageItem);
	///show a segment
	/*! 
	\param segItem contains a pointer to the BinaryImageTreeItem
	*/
	void segmentShow(const BinaryImageTreeItem *segItem );
	///hide a segment
	/*! 
	\param segItem contains a pointer to the BinaryImageTreeItem
	*/
	void segmentHide(const BinaryImageTreeItem *segItem );
	///show a perfusion map
	/*! 
	\param perfItem contains a pointer to the BinaryImageTreeItem
	*/
	void perfusionMapShow( RealImageTreeItem *perfItem );
	///hide a perfusion map
	/*! 
	\param perfItem contains a pointer to the BinaryImageTreeItem
	*/
	void perfusionMapHide(const RealImageTreeItem *perfItem );
	
	///Callback to update the widgets
	static void updateFunc(vtkObject* caller, long unsigned int eventId, void* clientData, void* callData );

	CTImageTreeModel imageModel;
	CTImageTreeItem::ConnectorHandle displayedCTImage;

	typedef std::set< BinaryImageTreeItem::ConnectorHandle > DisplayedSegmentContainer;
    DisplayedSegmentContainer displayedSegments;

	typedef std::set< RealImageTreeItem::ConnectorHandle > DisplayedPerfusionMapContainer;
    DisplayedPerfusionMapContainer displayedPerfusionMaps;


	static const DicomTagList CTModelHeaderFields;
    int pendingAction;

	bool oneWindowIsMax;
	//TacDialog* m_tacDialog;
	//MMID4Analyzer* mmid4Analyzer;
	MaxSlopeAnalyzer* maxSlopeAnalyzer;

	QwtPlotMarker *markerStart, *markerEnd;
    QwtPlotMarker *markerPickerX, *markerPickerY;
	QwtPlotGrid *grid;
	QwtPlotPicker *picker;
	vtkLookupTable *m_perfusionColorMap;
};

#endif // KardioPerfusion_H
