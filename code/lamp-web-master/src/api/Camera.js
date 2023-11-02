import axiosApi from './AxiosApi.js'


const apiList = {
  page: {
    method: 'POST',
    url: `/camera/camera/page`,
  },

//---------------------------------------------------------------------------------------
  update: {
    method: 'POST',
    url: `/camera/camera`
    //url:'/ecn/ecnupdate'                       //修改
  },


//----------------------------------------------------------------------------------------

  save: {
    method: 'PUT',
    url: `/camera/camera`
    //url:'/ecn/ecnadd'               //新增
  },


  //=====================================================================================
  delete: {
    method: 'DELETE',
    url: `/camera/camera`
    //url: `/ecn/ecndelect`                            //删除
  },

  //=====================================================================================
  preview: {
    method: 'POST',
    url: `/api/camera/camera/preview`
  },
  export: {
    method: 'POST',
    url: `/api/camera/camera/export`
  },
  import: {
    method: 'POST',
    url: `/api/camera/camera/import`
    //url:'/ecn/ecnadd'               //新增
  },
    //=====================================================================================
  search: {
    method: 'query',
    url: `/camera/camera/query`
  }
}






export default {
  search(data) {
    return axiosApi({
        ...apiList.search,
        data
    })
  },
  page (data) {
    return axiosApi({
      ...apiList.page,
      data
    })
  },
  save (data) {
    return axiosApi({
      ...apiList.save,
      data
    })
  },


//--------------------------------------------------------
  update (data) {
    return axiosApi({
      ...apiList.update,
      data
    })
  },

//---------------------------------------------------------


  delete (data) {

    return axiosApi({
      ...apiList.delete,
      data
    })
  },
  preview (data) {
    return axiosApi({
      ...apiList.preview,
      data
    })
  },
  export (data) {
    return axiosApi({
      ...apiList.export,
      responseType: "blob",
      data
    })
  },
  import (data) {
    return axiosApi({
      ...apiList.import,
      data
    })                          //新增
  }
}
