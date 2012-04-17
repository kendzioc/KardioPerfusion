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
#include "tacdialog.h"
#include <QMouseEvent>


#define VTK_CREATE(type, name) \
  vtkSmartPointer<type> name = vtkSmartPointer<type>::New()

// Forward Qt class declarations
class Ui_KardioPerfusion;
class DicomSelectorDialog;
class MultiPlanarReformatWidget;

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
	
	//void on_treeView_doubleClicked(const QModelIndex &index);

	///Action for clicking on treeView
	/*! 
	\param index contains the clicked index
	*/
	void on_treeView_clicked(const QModelIndex &index);
	///Action for changing the selection of the treeView
	/*! 
	\param selected contains the selected elements
	\param deselected contains the deselected elements
	*/
	void onSelectionChanged(const QItemSelection & selected, const QItemSelection & deselected);
	///Action for clicking on Draw-Button
	void on_btn_draw_clicked();
	///Action for clicking on RegionGrow-Button
	void on_btn_regionGrow_clicked();
	///Action for clicking on Erode-Button
	void on_btn_erode_clicked();
	///Action for clicking on Erode-Button
	void on_btn_dilate_clicked();
//	void on_btn_cannyEdges_clicked();
	///Action for clicking on Analyse-Button
	void on_btn_analyse_clicked();
	///Action for double clicking on a mprWidget
	void mprWidget_doubleClicked(MultiPlanarReformatWidget &w);
	///Slot for the contextmenu of the treeView
	/*! 
	\param pos contains the position of the contextmenu
	*/
	void treeViewContextMenu(const QPoint &pos);
	///creates a segment for selected image
	void createSegmentForSelectedImage();
	///changes the color for the selected item
	void changeColorForSelectedSegment();
	///removes a selected Image from the image model
	void removeSelectedImages();

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

	CTImageTreeModel imageModel;
	CTImageTreeItem::ConnectorHandle displayedCTImage;

	typedef std::set< BinaryImageTreeItem::ConnectorHandle > DisplayedSegmentContainer;
    DisplayedSegmentContainer displayedSegments;

	static const DicomTagList CTModelHeaderFields;
    int pendingAction;
	bool oneWindowIsMax;
	TacDialog* m_tacDialog;
};

#endif // KardioPerfusion_H
