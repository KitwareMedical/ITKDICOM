ITKDICOM
========

.. image:: https://circleci.com/gh/KitwareMedical/ITKDICOM/tree/master.svg?style=shield
    :target: https://circleci.com/gh/KitwareMedical/ITKDICOM/tree/master

Better support for DICOM in `ITK <https://itk.org/>`_.

Objectives:

- Write out valid DICOM images
- Ensure anonymization is possible

Approach:

- Write out images typed by their modality
- Whitelist a set of metadata / tags required per modality
- Whitelist metadata for anonymization
- Use `DCMTK <http://dicom.offis.de/>`_ for heavy lifting

This repository is currently a work in progress, and functional filters are
not yet available.
